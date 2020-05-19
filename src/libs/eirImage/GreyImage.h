// file:{EIRC2 repo}./src/libs/eirImage/GreyImage.h
#pragma once
#include "eirImage.h"

#include "Image.h"

class EIRIMAGE_EXPORT GreyImage : public Image
{
public:
    GreyImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Grayscale8);
    GreyImage(const QImage &image,
              const QImage::Format newFormat
          =QImage::Format_Invalid);

};

