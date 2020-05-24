// file:{EIRC2 repo}./src/libs/eirImage/BitImage.cpp
#include "BitImage.h"

#include <eirBase/Debug.h>

BitImage::BitImage(const QSize size,
             const QImage::Format format)
    : Image(size, format)
{
    TRACEQFI << size << format;
}

BitImage::BitImage(const QImage &image,
                     const QImage::Format newFormat)
    : Image(image, newFormat)
{
    TRACEQFI << image << newFormat;
}