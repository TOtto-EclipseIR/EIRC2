#pragma once
#include "eirImage.h"

#include <eirType/VarPak.h>

#include <QByteArray>
#include <QImage>

class QFileInfo;

#include "ColorImage.h"
#include "GreyImage.h"
#include "BaseImage.h"

class EIRIMAGE_EXPORT ImagePak : public VarPak
{
public:
    ImagePak();
    ImagePak(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
    ImagePak(const QFileInfo &fileInfo, const BaseImage &baseImage);
    void set(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
    void set(const QFileInfo &fileInfo, const BaseImage &baseImage);
    void set(const BaseImage &image);
    BaseImage image(const QImage::Format qformat);
    ColorImage colorImage();
    GreyImage greyImae();
};

