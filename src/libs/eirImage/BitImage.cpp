// file:{EIRC2 repo}./src/libs/eirImage/BitImage.cpp
#include "BitImage.h"

#include <eirXfr/Debug.h>

BitImage::BitImage(const QSize size,
             const QImage::Format format)
    : BaseImage(size, format)
{
    TRACEQFI << size << format;
}

BitImage::BitImage(const QImage &image,
                     const QImage::Format newFormat)
    : BaseImage(image, newFormat)
{
    TRACEQFI << image << newFormat;
}
