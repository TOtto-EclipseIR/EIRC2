// file:{EIRC2 repo}./src/libs/eirImage/BaseImage.h
//! \file Image.h
#pragma once
#include "eirImage.h"

#include <QImage>
#include <QVariant>
class QByteArray;

class EIRIMAGE_EXPORT
        BaseImage
{
public:
    enum Option
    {
        nullOption = 0,
        GreyFormat = 0x00000001,
        MakeSquare = 0x80000000,
    };
     Q_DECLARE_FLAGS(Options, Option)

public:
    BaseImage(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Invalid);
    BaseImage(const QImage &image,
          const QImage::Format newFormat
            =QImage::Format_Invalid);
    BaseImage(const QByteArray &bytes,
          const QImage::Format newFormat
            =QImage::Format_Invalid);
    QImage image() const;
    QImage &image();
    Option constOptions() const;
    Option &options();
    bool isNull() const;
    QSize size() const;
    QImage::Format format() const;
    int formatInt() const;
    QVariant toVariant() const;
    QString toString() const;

private:
    QImage::Format mFormat=QImage::Format_Invalid;
    QImage mImage;
    Option mOptions;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(BaseImage::Options)
