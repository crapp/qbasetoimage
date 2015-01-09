#include "filesaveoperation.h"

FileSaveOperation::FileSaveOperation(std::shared_ptr<QImage> img,
                                     QString file) :
    img(img), file(file)
{

}

FileSaveOperation::~FileSaveOperation()
{

}

void FileSaveOperation::run()
{
    bool retVal = this->saveImage();
    emit saveopfinished(retVal);
}

bool FileSaveOperation::saveImage()
{
    return this->img->save(this->file);
}

