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
}

