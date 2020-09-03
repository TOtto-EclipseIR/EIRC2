#include "QQImage.h"

#include <QImageReader>
#include <QImageWriter>

QQImage::QQImage() {;}
QQImage::QQImage(const QImage &other) : QImage(other) {;}
QQImage::QQImage(const QString &fileName, const char *format) : QImage(fileName, format) {;}

int QQImage::rows() const
{
    return size().height();
}

int QQImage::cols() const
{
    return size().width();
}

QStringList QQImage::supportedReadFormats()
{
    QStringList supportedFormatStrings;
    QByteArrayList supportedFormatBAs
            = QImageReader::supportedImageFormats();
    foreach (QByteArray fmt, supportedFormatBAs)
        supportedFormatStrings << QString(fmt);
    return supportedFormatStrings;
}


