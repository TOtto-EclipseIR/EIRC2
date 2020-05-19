// file:{EIRC2 repo}./src/libs/eirImage/BaseImage.cpp
#pragma once
#include "eirImage.h"

#include <QImage>

class EIRIMAGE_EXPORT BaseImage : public QImage
{
public:
    BaseImage(const QImage::Format format=QImage::Format_Invalid);
};

