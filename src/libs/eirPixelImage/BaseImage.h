// file: {EIRC2 repo}./src/libs/eirPixelImage/BaseImage.h
#pragma once
#include "eirPixelImage.h"

#include <QImage>

#include <QSize>

class EIRPIXELIMAGE_EXPORT BaseImage : public QImage
{
public:
    BaseImage();
    BaseImage(const QImage &image);
    BaseImage(const QSize size,
              const Format format=QImage::Format_ARGB32);
    bool isGrey(void) const;
    bool isNull() const;
    bool isColor32Format() const;
    bool notColor32Format() const;

public: // static
    static bool isColor32Format(const QImage::Format imageformat);
    static bool isColor32Format(const QImage &image);

protected:
    const QImage cmBaseImage;
};

