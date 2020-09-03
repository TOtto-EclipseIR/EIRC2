#pragma once
#include "eirObjDet.h"

#include <QFileInfo>
#include <QQueue>

#include <eirType/QQFileInfo.h>
#include <eirType/ValuePak.h>
#include <eirImage/QQImage.h>

class EIROBJDET_EXPORT ObjDetPak : public ValuePak
{
public:
    enum ImageIndex
    {
        nullImageIndex = 0,
        InputImage,
        sizeImageIndex
    };

public:
    typedef QQueue<ObjDetPak> Queue;
public:
    ObjDetPak();
    ObjDetPak(const QQFileInfo &fileInfo, const bool load=true);
    ObjDetPak(const QByteArray &bytes, const bool load=true);
    QQFileInfo inputImageFileInfo() const;
    QByteArray inputImageBytes() const;
    void setInputFileInfo(const QQFileInfo &fileInfo);
    void setInputBytes(const QByteArray &bytes);
    void loadInputImage(const QQFileInfo &fileInfo);
    void loadInputImage(const QByteArray &bytes);
    void loadInputImage();

protected:
    void setImage(const ImageIndex iix,
                  const QQImage &image);

};

