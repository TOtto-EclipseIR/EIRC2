// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.cpp
#include "GreyImage.h"

#include <eirBase/Debug.h>

GreyImage::GreyImage(const QImage &image,
                     const QImage::Format newFormat)
    : Image(image, newFormat)
{
    TRACEQFI << image << newFormat;
}

GreyImage::GreyImage(const QSize size,
                     const QImage::Format format)
    : Image(size, format)
{
    TRACEQFI << size << format;
}
