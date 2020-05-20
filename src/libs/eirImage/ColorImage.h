// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.h
#pragma once
#include "eirImage.h"

#include "Image.h"

class EIRIMAGE_EXPORT ColorImage : public Image
{
public:
    ColorImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_ARGB32);
    ColorImage(const QImage &image,
              const QImage::Format newFormat
          =QImage::Format_Invalid);

};

