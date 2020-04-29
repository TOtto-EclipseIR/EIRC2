#include "GreyImage.h"

GreyImage::GreyImage(const BaseImage &baseImage)
    : cmBaseImage(baseImage)
{

}

GreyImage::GreyImage(const QSize size, const Format imgFormat)
    : BaseImage(size, imgFormat)
{

}
