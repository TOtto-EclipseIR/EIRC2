#include "ImagePak.h"

#include <QDir>
#include <QFileInfo>

#include <eirXfr/Debug.h>

#include "ImageInfo.h"

ImagePak::ImagePak() {;}

ImagePak::ImagePak(const QFileInfo &fileInfo, const BaseImage &baseImage)
{
    TRACEQFI << fileInfo << ImageInfo(baseImage)();
    NEEDDO(it);
}

ImagePak::ImagePak(const QFileInfo &fileInfo,
                   const QByteArray &encodedBytes)
{
    TRACEQFI << fileInfo << encodedBytes.size()
             << encodedBytes.left(16).toHex().toUpper();
    set(fileInfo, encodedBytes);
}

void ImagePak::set(const BaseImage &img)
{
    TRACEQFI << ImageInfo(img)();
    QImage::Format fmt = img.format();
    QVariant vari = img.image();
    MultiName name("Image/Format", QString::number(int(fmt)));
    Var var(name, vari, QImage(QSize(), fmt));
    VarPak::set(int(fmt), var);
}

void ImagePak::set(const QFileInfo &fileInfo,
                   const QByteArray &encodedBytes)
{
    TRACEQFI << fileInfo << encodedBytes.size()
             << encodedBytes.left(16).toHex().toUpper();

    MultiName imageName(MultiName(fileInfo.dir().path()),
                        MultiName(fileInfo.completeBaseName()));
    VarPak::id().set(QUuid(imageName));
    VarPak::id().set(imageName);
    VarPak::set(encodedBytes);
}
