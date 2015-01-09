#ifndef FILESAVEOPERATION_H
#define FILESAVEOPERATION_H

#include <memory>

#include <QObject>
#include <QThread>
#include <QImage>

class FileSaveOperation : public QThread
{
    Q_OBJECT
public:
    explicit FileSaveOperation(std::shared_ptr<QImage> img = nullptr,
                               QString file = "");
    ~FileSaveOperation();

    void run();

signals:
    void saveopfinished(bool status);

public slots:


private:
    QString file;
    std::shared_ptr<QImage> img;

    bool saveImage();
};

#endif // FILESAVEOPERATION_H
