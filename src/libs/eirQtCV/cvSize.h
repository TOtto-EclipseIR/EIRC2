#pragma once
#include "eirQtCV.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

#include <QSize>

class EIRQTCV_EXPORT cvSize : public cv::Size
{
public:
    cvSize(const QSize qsize);
};

