//! \file cvMat.h
#pragma once
#include "eirHaar.h"

class QImage;

#include <eirImage/Image.h>

#include "cvFormat.h"


class EIRHAAR_EXPORT cvMat : public cv::Mat
{
public:
    cvMat();
    cvMat(const Image &image, const cvFormat &cvfmt=cvFormat());
    bool set(const Image &image, const cvFormat=cvFormat());
    Image toImage(const QImage::Format newFormat=QImage::Format_Invalid);
};

