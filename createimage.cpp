#include "createimage.h"

CreateImage::CreateImage(std::shared_ptr<QImage> img, QByteArray barray) :
    img(img), barray(barray)
{

}

CreateImage::~CreateImage()
{

}

void CreateImage::run()
{
    bool status = this->createImage();
    emit imageReady(status);
}

bool CreateImage::createImage()
{
    if (this->img)
        return this->img->loadFromData(QByteArray::fromBase64(this->barray));

    return false;
}
