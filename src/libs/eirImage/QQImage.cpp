#include "QQImage.h"

#include <QImageReader>
#include <QImageWriter>

QQImage::QQImage() {;}
QQImage::QQImage(const QImage &other) : QImage(other) {;}
QQImage::QQImage(const QString &fileName, const char *format) : QImage(fileName, format) {;}

QStringList QQImage::supportedReadFormats()
{
    QStringList supportedFormatStrings;
    QByteArrayList supportedFormatBAs
            = QImageReader::supportedImageFormats();
    foreach (QByteArray fmt, supportedFormatBAs)
        supportedFormatStrings << QString(fmt);
    return supportedFormatStrings;
}


