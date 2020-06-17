// file:{EIRC2 repo}./src/libs/eirImage/BitImage.h
#pragma once
#include "eirImage.h"

#include "BaseImage.h"

class EIRIMAGE_EXPORT BitImage : public BaseImage
{
public:
    BitImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Mono);
    BitImage(const QImage &image,
          const QImage::Format newFormat
          =QImage::Format_Mono);
};

