// file:{EIRC2 repo}./src/libs/eirImage/Image.h
#pragma once
#include "eirImage.h"

#include <QImage>

#include "ImageFormat.h"

class EIRIMAGE_EXPORT Image : public QImage
{
public:
    Image(ImageFormat format=ImageFormat::nullFormat);
};

