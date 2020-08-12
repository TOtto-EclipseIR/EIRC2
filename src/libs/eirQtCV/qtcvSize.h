// file:{EIRC2 repo}./src/libs/eirQtCV/qtcvSize.h
#pragma once
#include "eirQtCV.h"

#include <QSize>

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

//typedef cv::Size cvSize;

class EIRQTCV_EXPORT qtcvSize : public cv::Size
{
public:
    qtcvSize();
    qtcvSize(const QSize qsz);
    void set(const cv::Size cvsz);
    cv::Size cvsize() const;
    cv::Size operator ()() const;
};

