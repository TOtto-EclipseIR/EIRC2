// file:{EIRC2 repo}./src/libs/eirImage/BaseImage.cpp
//! \file Image.cpp
#include "BaseImage.h"

#include <eirXfr/Debug.h>

#include "ImageInfo.h"

BaseImage::BaseImage(const QSize size,
             const QImage::Format format)
    : mFormat(format)
    , mImage(size, format)
{
    TRACEQFI << size << format;
}

BaseImage::BaseImage(const QImage &image, const QImage::Format newFormat)
    : mFormat(newFormat)
    , mImage(image)
{
    TRACEQFI << image.size() << newFormat;
    if (mImage.format() != newFormat)
        mImage.convertTo(mFormat);
}

BaseImage::BaseImage(const QByteArray &bytes,
             const QImage::Format newFormat)
    : mFormat(newFormat)
    , mImage(bytes)
{
    TRACEQFI << bytes.size() << newFormat;
    if (mImage.format() != newFormat)
        mImage.convertTo(mFormat);
}

QImage BaseImage::image() const
{
    return mImage;
}

QImage &BaseImage::image()
{
    return mImage;
}

BaseImage::Option BaseImage::constOptions() const
{
    return mOptions;
}

BaseImage::Option &BaseImage::options()
{
    return mOptions;
}

bool BaseImage::isNull() const
{
    return mImage.isNull();
}

QSize BaseImage::size() const
{
    return mImage.size();
}

QImage::Format BaseImage::format() const
{
    return mImage.format();
}

int BaseImage::formatInt() const
{
    int formatInt = mImage.format();
    return formatInt;
}

QVariant BaseImage::toVariant() const
{
    QVariant variant = image();
    return variant;
}

QString BaseImage::toString() const
{
    return ImageInfo(mImage).toString();
}
