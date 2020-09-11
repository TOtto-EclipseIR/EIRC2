#include "Frame.h"

#include <QDir>

Frame::Frame(const QFileInfo fileInfo)
{
    set(QImage(fileInfo.filePath()));
}

Frame::Frame(const QFileInfo fileInfo, const QImage image)
{
    set(image);
    set(fileInfo);
}

void Frame::set(const QImage &image)
{
    *(QImage *)this = image;
}

void Frame::set(const QFileInfo &fileInfo)
{
    QImage::setText("FileInfoDir", fileInfo.dir().path());
    QImage::setText("FileInfoName", fileInfo.fileName());

}

QFileInfo Frame::fileInfo() const
{
    return QFileInfo(QDir(QImage::text("FileInfoDir")),
                     QImage::text("FileInfoName"));
}
