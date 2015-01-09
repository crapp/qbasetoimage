//   Copyright 2012-2015 Christian Rapp 0x2a@posteo.org

//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//       http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("QBaseToImage");

    QString startTextFile = QDir::homePath() + "/qbasetoimage.png";
    this->outFile = startTextFile;

    ui->lineEdit->setText(startTextFile);
    ui->centralWidget->setWindowTitle("QBaseToImage");

    ui->plainTextEdit->setFocus();

    // connect needed "static" signals
    connect(ui->selectFileButton, SIGNAL(clicked()), this, SLOT(getSaveFile()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFileToDisk()));
    connect(ui->previewButton, SIGNAL(clicked()), this, SLOT(openPreviewDialog()));
    connect(ui->lineEdit, SIGNAL(textEdited( const QString & )), this, SLOT(outFileChanged( const QString & )));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(generateImage()));

    ui->plainTextEdit->setPlainText(QTICON);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSaveFile()
{
    this->outFile = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp *.gif)"));
    if (!this->outFile.isEmpty())
        ui->lineEdit->setText(this->outFile);
}

void MainWindow::saveFileToDisk()
{
    if (!this->outFile.isEmpty())
    {
        ui->labelStatus->setText("Saving image, please wait...");

        // TODO: This looks not very clever
        ui->plainTextEdit->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->previewButton->setEnabled(false);
        ui->selectFileButton->setEnabled(false);

        this->fso = std::unique_ptr<FileSaveOperation>(
                    new FileSaveOperation(this->img,
                                          this->outFile));

        // connect to finished signal after we initialized the unique pointer
        connect(this->fso.get(), SIGNAL(saveopfinished(bool)), this, SLOT(fileSaved(bool)));

        // start file saving
        this->fso->start();
    }
}

void MainWindow::fileSaved(bool status)
{
    if (status)
    {
        ui->labelStatus->setText("Done");
    } else {
        ui->labelStatus->setText("Failed");
    }
    ui->plainTextEdit->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->previewButton->setEnabled(true);
    ui->selectFileButton->setEnabled(true);

    // make sure the thread has finished
    this->fso->wait();
}

void MainWindow::outFileChanged(const QString & path)
{
    if (!path.isEmpty())
        this->outFile = path;
}

void MainWindow::openPreviewDialog()
{
    this->prevDialog = std::unique_ptr<PreviewDialog>(new PreviewDialog(this->img, this));
    // open modal
    this->prevDialog->exec();
}

void MainWindow::generateImage()
{
    if (ui->plainTextEdit->toPlainText().trimmed().isEmpty())
        return;

    // disable buttons and plaintext
    ui->saveButton->setEnabled(false);
    ui->previewButton->setEnabled(false);
    ui->plainTextEdit->setEnabled(false);

    // FIXME: Should use QStatusBar instead of this custom label
    ui->labelStatus->setText("Creating image, please wait...");

    // Fix for different Qt versions
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    // get byte array from plaintext
    QByteArray base64Data = ui->plainTextEdit->toPlainText().toAscii();
#else
    // get byte array from plaintext
    QByteArray base64Data = ui->plainTextEdit->toPlainText().toLatin1();
#endif


    this->img = std::make_shared<QImage>();

    this->cimage = std::unique_ptr<CreateImage>(new CreateImage(
                                                    this->img,
                                                    base64Data));

    // connect to image ready signal
    connect(this->cimage.get(), SIGNAL(imageReady(bool)), this, SLOT(imageReady(bool)));

    // start the thread
    this->cimage->start();
}

void MainWindow::imageReady(bool status)
{
    this->cimage->wait();
    if (status)
    {
        ui->saveButton->setEnabled(true);
        ui->previewButton->setEnabled(true);
        ui->labelStatus->setText("Image created");
    } else {
        ui->labelStatus->setText("Could not create Image");
    }

    ui->plainTextEdit->setEnabled(true);
}

