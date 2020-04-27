#pragma once

#include <eirType/QQRect.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

class qRect : public QQRect
{
public:
    qRect();
    qRect(const cv::Rect &cvrc);
    void set(const cv::Rect &cvrc);
};

