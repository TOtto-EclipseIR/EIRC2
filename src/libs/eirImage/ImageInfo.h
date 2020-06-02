#pragma once

#include <QByteArray>
#include <QFileInfo>
#include <QImage>

#include "Image.h"
#include "ImageFlags.h"

class ImageInfo
{
public:
    ImageInfo();
    ImageInfo(const QByteArray &bytes,
              const QFileInfo &fileInfo=QFileInfo());
    ImageInfo(const Image &baseImage,
              const QFileInfo &fileInfo=QFileInfo());
    bool set();
    bool set(const Image &baseImage);
    QString toString() const;
    operator QString () const;
    QString operator ()() const;

private:
    Image mBaseImage;
    QFileInfo mFileInfo;
    ImageFlags mFlags;
    QImage::Format mImageFormat=QImage::Format_Invalid;
};

