// file:{EIRC2 repo}./src/libs/eirImage/ColorImage.cpp
#include "ColorImage.h"

#include <eirBase/Debug.h>

ColorImage::ColorImage(const QImage &image,
                     const QImage::Format newFormat)
    : Image(image, newFormat)
{
    TRACEQFI << image << newFormat;
}

ColorImage::ColorImage(const QSize size,
                     const QImage::Format format)
    : Image(size, format)
{
    TRACEQFI << size << format;
}
