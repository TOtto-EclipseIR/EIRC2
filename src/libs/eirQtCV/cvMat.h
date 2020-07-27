#pragma once
#include "eirQtCV.h"

#include <QImage>
#include <set>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

class EIRQTCV_EXPORT cvMat : public cv::Mat
{
public:
    cvMat();
    bool set(const cv::Mat other);
    bool set(const QImage &qimage);
    void clear();
};

