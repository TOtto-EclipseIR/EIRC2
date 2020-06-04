#pragma once

#include <eirBase/VarPak.h>

#include <QByteArray>
#include <QImage>

class QFileInfo;

#include "Image.h"

class ImagePak : public VarPak
{
public:
    ImagePak();
    ImagePak(const QFileInfo &fileInfo, const Image &baseImage);
    ImagePak(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
    void set(const QFileInfo &fileInfo, const Image &baseImage);
    void set(const QFileInfo &fileInfo, const QByteArray &encodedBytes);
};

