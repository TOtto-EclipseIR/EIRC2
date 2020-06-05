#pragma once

#include <eirBase/VarPak.h>

#include <QByteArray>
#include <QImage>

class QFileInfo;

#include "ColorImage.h"
#include "GreyImage.h"
#include "Image.h"

class ImagePak : public VarPak
{
public:
    ImagePak();
    ImagePak(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
    ImagePak(const QFileInfo &fileInfo, const Image &baseImage);
    void set(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
    void set(const QFileInfo &fileInfo, const Image &baseImage);
    void set(const Image &image);
    Image image(const QImage::Format qformat);
    ColorImage colorImage();
    GreyImage greyImae();
};

