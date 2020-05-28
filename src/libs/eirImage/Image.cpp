// file:{EIRC2 repo}./src/libs/eirImage/Image.cpp
#include "Image.h"

#include <eirBase/Debug.h>

Image::Image(const QSize size,
             const QImage::Format format)
    : mFormat(format)
    , mImage(size, format)
{
    TRACEQFI << size << format;
}

Image::Image(const QImage &image,
             const QImage::Format newFormat)
    : mFormat(newFormat)
    , mImage(image)
{
    TRACEQFI << image << newFormat;
    if (mImage.format() != newFormat)
        mImage.convertTo(mFormat);
}

QImage Image::constImage() const
{
    return mImage;
}

QImage &Image::image()
{
    return mImage;
}

Image::Option Image::constOptions() const
{
    return mOptions;
}

Image::Option &Image::options()
{
    return mOptions;
}

bool Image::isNull() const
{
    return mImage.isNull();
}

QSize Image::size() const
{
    return mImage.size();
}

