#ifndef CREATEIMAGE_H
#define CREATEIMAGE_H

#include <memory>

#include <QObject>
#include <QThread>
#include <QImage>

class CreateImage : public QThread
{

    Q_OBJECT
public:
    explicit CreateImage(std::shared_ptr<QImage> img, QByteArray barray);
    ~CreateImage();

    void run();

signals:
    void imageReady(bool status);

private:

    std::shared_ptr<QImage> img;
    QByteArray barray;

    bool createImage();

};

#endif // CREATEIMAGE_H
