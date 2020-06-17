// file:{EIRC2 repo}./src/libs/eirImage/IndexedImage.h
#pragma once
#include "eirImage.h"

#include "BaseImage.h"
#include "ColorTable.h"

class EIRIMAGE_EXPORT IndexedImage : public BaseImage
{
public:
    IndexedImage(const ColorTable &colorTable=ColorTable(),
                 const QSize size=QSize(),
                 const QImage::Format format
                      =QImage::Format_Grayscale8);
    IndexedImage(const QImage &image,
                 const ColorTable &newColorTable=ColorTable(),
                 const QImage::Format newFormat
                     =QImage::Format_Invalid);
private:
    ColorTable mColorTable;
};

