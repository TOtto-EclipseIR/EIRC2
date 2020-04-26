// file: {EIRC2 repo}./src/libs/eirQtCV/cvRect.h
#pragma once
#include "eirQtCV4.h"

#include <opencv2/core.hpp>

#include <eirType/QQRect.h>

class EIRQTCV4_EXPORT cvRect : public QQRect
{
public:
    cvRect();
    cvRect(const cv::Rect &cvrc);
    void set(const cv::Rect &cvrc);
};

