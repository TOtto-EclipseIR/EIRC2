//! \file cvFormat.h
#pragma once
#include "eirHaar.h"

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
typedef int cvMatType;


class EIRHAAR_EXPORT cvFormat
{
public:
    typedef int cvMatType;

public:
    cvFormat();
    cvFormat(const QImage::Format qiFormat);
    cvFormat(const cvMatType other);
    int toInt() const;
    int operator () () const;
    cvMatType fromImage(const QImage::Format qiFormat);
    QImage::Format toImage() const;

public: // static
    static cvMatType QtToCvFormat(QImage::Format qtFormat);
    static QImage::Format CvToQtFormat(const cvMatType cvFormat);

private:
    cvMatType mType=0;
};
