// file:{EIRC2 repo}./src/libs/eirImage/ColorImage.cpp
#include "ColorImage.h"

#include <eirBase/Debug.h>

ColorImage::ColorImage(const QImage &image,
                     const QImage::Format newFormat)
    : BaseImage(image, newFormat)
{
    TRACEQFI << image << newFormat;
}

ColorImage::ColorImage(const QSize size,
                     const QImage::Format format)
    : BaseImage(size, format)
{
    TRACEQFI << size << format;
}
