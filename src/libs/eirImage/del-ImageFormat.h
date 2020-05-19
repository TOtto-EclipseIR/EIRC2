// file:{EIRC2 repo}./src/libs/eirImage/ImageFormat.h
#pragma once

#include <QImage>

#include <eirBase/BasicName.h>
#include <eirType/DualMap.h>

class EIRTYPE_EXPORT ImageFormat : public Enumeration
{
public:
    enum FormatEnum
    {
        nullFormat = 0,
        Mono = QImage::Format::Mono,
    };

public:
    QImage::Format toQImage() const;

private:
    FormatEnum mEnum;
    static DualMap<FormatEnum, BasicName>
};
