// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.h
#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT ColorImage : public BaseImage
{
public:
    ColorImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_ARGB32);
    ColorImage(const QImage &image,
              const QImage::Format newFormat
          =QImage::Format_Invalid);

};

