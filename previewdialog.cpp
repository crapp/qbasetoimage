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

#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(std::shared_ptr<QImage> img, QWidget *parent) :
    QDialog(parent),
    img(img),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);

    if (this->img->width() > ui->PreviewLabel->width() ||
            this->img->height() > ui->PreviewLabel->height())
    {
        ui->PreviewLabel->setPixmap(QPixmap::fromImage(*(this->img.get())).scaled(
                                    ui->PreviewLabel->height(),
                                    ui->PreviewLabel->width(),
                                    Qt::KeepAspectRatio));
    } else {
        ui->PreviewLabel->setPixmap(QPixmap::fromImage(*(this->img.get())));
    }

}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}
