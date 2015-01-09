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

#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <memory>

#include <QDialog>

namespace Ui {
class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    // Is it save to change the argument order of such a constructor?
    explicit PreviewDialog(std::shared_ptr<QImage> img, QWidget *parent = 0);
    ~PreviewDialog();

private:
    std::shared_ptr<QImage> img;

    Ui::PreviewDialog *ui;

};

#endif // PREVIEWDIALOG_H
