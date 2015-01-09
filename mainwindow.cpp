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

    QString startText = QString::fromUtf8("Daten per Copy&Paste einfügen");
    QString startTextFile = QString::fromUtf8("Speicherort, -datei auswählen -->");

    ui->plainTextEdit->setPlainText(startText);
    ui->lineEdit->setText(startTextFile);
    ui->centralWidget->setWindowTitle("QBaseToImage");

    connect(ui->selectFileButton, SIGNAL(clicked()), this, SLOT(getSaveFile()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(base64Decode()));
    connect(ui->previewButton, SIGNAL(clicked()), this, SLOT(openPreviewDialog()));
    connect(ui->lineEdit, SIGNAL(textEdited( const QString & )), this, SLOT(outFileChanged( const QString & )));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(generateImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSaveFile()
{
    this->outFile = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/saedelaere", tr("Image Files (*.png *.jpg *.bmp *.gif)"));
    if (!this->outFile.isEmpty())
        ui->lineEdit->setText(this->outFile);
}

void MainWindow::base64Decode()
{

    this->img->save(this->outFile);
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
    QByteArray base64Data = ui->plainTextEdit->toPlainText().toAscii();
    this->img = std::make_shared<QImage>();
    this->img->loadFromData(QByteArray::fromBase64(base64Data));
    if (!this->img->isNull())
    {
        ui->saveButton->setEnabled(true);
        ui->previewButton->setEnabled(true);
    } else {
        ui->saveButton->setEnabled(false);
        ui->previewButton->setEnabled(false);
    }
}

