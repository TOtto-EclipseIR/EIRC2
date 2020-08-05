#pragma once
#include "eirQtCV.h"

#include <QImage>
#include <QSize>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

class EIRQTCV_EXPORT cvMat //: public cv::Mat
{
public:
    cvMat();
    bool set(const cv::Mat other);
    void set(const QSize sz);
    bool set(const QImage &qimage);
    void clear();

private:
    cv::Mat mCvMat;
};

