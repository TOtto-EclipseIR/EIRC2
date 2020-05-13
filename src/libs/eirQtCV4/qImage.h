#pragma once

#include <QImage>

#include "cvMat.h"

class qImage : public QImage
{
public:
    qImage();
    qImage(const QImage & img);
    void set(const QImage &img);
    cvMat toCVMat() const;
};

