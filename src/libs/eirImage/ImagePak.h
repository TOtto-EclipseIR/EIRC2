#pragma once

#include <eirBase/VarPak.h>

#include <QImage>

class QFileInfo;

#include "Image.h"

class ImagePak : public VarPak
{
public:
    ImagePak();
    ImagePak(const QFileInfo &fileInfo, const Image &baseImage);
};

