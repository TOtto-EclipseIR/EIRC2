// file: {EIRC2 repo}./src/libs/eirPixelImage/GreyAverageImage.h
#pragma once
#include "eirPixelImage.h"

#include "BaseImage.h"

#include "ColorImage.h"

class EIRPIXELIMAGE_EXPORT GreyAverageImage : BaseImage
{
public:
    GreyAverageImage();
    ColorImage greyAverageImage();
    ColorImage create(ColorImage greyColorImage);
    ColorImage subjectImage() const;
    ColorImage greyAverageImage() const;
    bool isGrey();
    QImage image() const;

protected:

private:
    ColorImage mSubjectImage;
    ColorImage mGreyAverageImage;
};

