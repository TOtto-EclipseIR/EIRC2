// file:{EIRC2 repo}./src/libs/eirImage/Image.h
//! \file Image.h
#pragma once
#include "eirImage.h"

#include <QImage>
class QByteArray;

class EIRIMAGE_EXPORT Image
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
    Image(const QSize size=QSize(),
          const QImage::Format format
          =QImage::Format_Invalid);
    Image(const QImage &image,
          const QImage::Format newFormat
            =QImage::Format_Invalid);
    Image(const QByteArray &bytes,
          const QImage::Format newFormat
            =QImage::Format_Invalid);
    QImage constImage() const;
    QImage &image();
    Option constOptions() const;
    Option &options();
    bool isNull() const;
    QSize size() const;
    QString toString() const;

private:
    QImage::Format mFormat=QImage::Format_Invalid;
    QImage mImage;
    Option mOptions;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Image::Options)
