// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.cpp
#include "GreyImage.h"

#include <eirXfr/Debug.h>

GreyImage::GreyImage(const QImage &image,
                     const QImage::Format newFormat)
    : BaseImage(image, newFormat)
{
    TRACEQFI << image << newFormat;
}

GreyImage::GreyImage(const QSize size,
                     const QImage::Format format)
    : BaseImage(size, format)
{
    TRACEQFI << size << format;
}
