// file: {EIRC2 repo}./src/libs/eirPixelImage/ColorImage.h
#include "ColorImage.h"

ColorImage::ColorImage(const BaseImage &baseImage)
    : BaseImage(baseImage)
{

}

ColorImage::ColorImage(const QImage &image)
    : BaseImage(image)
{

}

ColorImage::ColorImage(const QSize size,
                       const QImage::Format imgFormat)
    : BaseImage(BaseImage(size, imgFormat))
{

}

