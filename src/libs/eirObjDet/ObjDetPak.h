#pragma once
#include "eirObjDet.h"

#include <QFileInfo>
#include <QQueue>

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
    ObjDetPak(const QFileInfo &fileInfo,
              const bool andLoad=true);
    QFileInfo inputFileInfo() const;
    void setInputFileInfo(const QFileInfo &fileInfo);
    void setInputBytes(const QByteArray &bytes);
    void setImage(const ImageIndex iix,
                  const MultiName &valueName,
                  const QQImage &image);
    void loadInputFile(const QFileInfo &fileInfo);
};

