// file: {EIRC2 repo}./src/libs/eirQtCV/cvRect.h
#pragma once
#include "eirQtCV4.h"

#include <opencv2/core.hpp>

#include <eirType/QQRect.h>

class EIRQTCV4_EXPORT cvRect : public cv::Rect
{
public:
    cvRect();
    cvRect(const cv::Rect &cvrc);
    void set(const QQRect &qqrc);
    QQRect qRect() const;
    operator QQRect() const;
};

