#include "ImageInfo.h"

#include <eirXfr/Debug.h>

ImageInfo::ImageInfo()
{

}

ImageInfo::ImageInfo(const BaseImage &baseImage, const QFileInfo &fileInfo)
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

bool ImageInfo::set(const BaseImage &baseImage)
{
    mBaseImage = baseImage;
    return set();
}

ImageInfo::ImageInfo(const QByteArray &bytes, const QFileInfo &fileInfo)
    : mBaseImage(BaseImage(bytes))
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

