#pragma once
#include "eirQtCV.h"

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

class EIRQTCV_EXPORT cvMat : public cv::Mat
{
public:
    cvMat();
    bool set(const QImage &qimage);
};
