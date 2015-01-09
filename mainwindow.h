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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QFileDialog>
#include <QByteArray>

#include "previewdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void getSaveFile();
    void base64Decode();
    void outFileChanged(const QString &);
    
private:
    Ui::MainWindow *ui;
    QString outFile;
    std::shared_ptr<QImage> img;

    std::unique_ptr<PreviewDialog> prevDialog;

private slots:

    void generateImage();
    void openPreviewDialog();

};

#endif // MAINWINDOW_H
