// file:{EIRC2 repo}./src/libs/eirImage/Image.h
#pragma once
#include "eirImage.h"

#include <QImage>

class EIRIMAGE_EXPORT Image
{
public:
    Image(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Invalid);
    Image(const QImage &image,
          const QImage::Format newFormat
          =QImage::Format_Invalid);

private:
    QImage::Format mFormat=QImage::Format_Invalid;
    QImage mImage;

};

