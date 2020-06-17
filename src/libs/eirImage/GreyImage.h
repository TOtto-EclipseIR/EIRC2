// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.h
#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT GreyImage : public BaseImage
{
public:
    GreyImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Grayscale8);
    GreyImage(const QImage &image,
              const QImage::Format newFormat
          =QImage::Format_Invalid);

};

