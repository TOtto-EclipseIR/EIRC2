#pragma once

#include "BaseImage.h"

class GreyImage : public BaseImage
{
public:
    GreyImage(const BaseImage &baseImage);
    GreyImage(const QSize size,
              const QImage::Format imgFormat=QImage::Format_Grayscale8);

private:
    const BaseImage cmBaseImage;
};

