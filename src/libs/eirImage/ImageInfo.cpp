#include "ImageInfo.h"

#include <eirBase/Debug.h>

ImageInfo::ImageInfo()
{

}

ImageInfo::ImageInfo(const Image &baseImage, const QFileInfo &fileInfo)
    : mBaseImage(baseImage)
    , mFileInfo(fileInfo)
{
    TRACEQFI << baseImage.size() << fileInfo;
    set();
}

bool ImageInfo::set()
{
    TRACEFN
    NEEDDO(it)
    return false;
}

bool ImageInfo::set(const Image &baseImage)
{
    mBaseImage = baseImage;
    return set();
}

ImageInfo::ImageInfo(const QByteArray &bytes, const QFileInfo &fileInfo)
    : mBaseImage(Image(bytes))
    , mFileInfo(fileInfo)
{
    TRACEQFI << bytes.size() << fileInfo;
    set();
}


QString ImageInfo::toString() const
{
    return QString("%");
}

ImageInfo::operator QString() const
{
    return toString();
}

QString ImageInfo::operator ()() const
{
    return toString();
}

