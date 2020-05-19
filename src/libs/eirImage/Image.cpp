// file:{EIRC2 repo}./src/libs/eirImage/Image.cpp
#include "Image.h"

#include <eirBase/Debug.h>

Image::Image(ImageFormat format)
    : QImage(QSize(), format.toQImage())
{
    TRACEQFI << format;
}
