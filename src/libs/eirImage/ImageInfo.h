#pragma once

#include <QByteArray>
#include <QFileInfo>
#include <QImage>

#include "BaseImage.h"
#include "ImageFlags.h"

class ImageInfo
{
public:
    ImageInfo();
    ImageInfo(const QByteArray &bytes,
              const QFileInfo &fileInfo=QFileInfo());
    ImageInfo(const BaseImage &baseImage,
              const QFileInfo &fileInfo=QFileInfo());
    bool set();
    bool set(const BaseImage &baseImage);
    QString toString() const;
    operator QString () const;
    QString operator ()() const;

private:
    BaseImage mBaseImage;
    QFileInfo mFileInfo;
    ImageFlags mFlags;
    QImage::Format mImageFormat=QImage::Format_Invalid;
};

