// file: {EIRC2 repo}./src/libs/eirPixelImage/ColorImage.h
#pragma once
#include "eirPixelImage.h"

#include "BaseImage.h"

class EIRPIXELIMAGE_EXPORT ColorImage : public BaseImage
{
public:
    ColorImage(const BaseImage &baseImage=BaseImage());
    ColorImage(const QImage &image);
    ColorImage(const QSize size,
               const QImage::Format imgFormat=QImage::Format_ARGB32);
//    BaseImage image() const;

protected:
//    const BaseImage cmBaseImage;
};

