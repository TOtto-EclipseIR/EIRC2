#include "ImagePak.h"

#include <QDir>
#include <QFileInfo>

#include <eirBase/Debug.h>

#include "ImageInfo.h"

ImagePak::ImagePak() {;}

ImagePak::ImagePak(const QFileInfo &fileInfo, const Image &baseImage)
{
    TRACEQFI << fileInfo << ImageInfo(baseImage)();

}

ImagePak::ImagePak(const QFileInfo &fileInfo,
                   const QByteArray &encodedBytes)
{
    TRACEQFI << fileInfo << encodedBytes.size()
             << encodedBytes.left(16).toHex().toUpper();
    MultiName imageName(MultiName(fileInfo.dir().path()),
                        MultiName(fileInfo.completeBaseName()));
    id().create(imageName());
}

void ImagePak::set(const QFileInfo &fileInfo, const Image &baseImage)
{

}
