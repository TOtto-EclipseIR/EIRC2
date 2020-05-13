// file; {EIRC2 repo}./src/libs/eirQtCV4/cvMat.h
#pragma once
#include "eirQtCV4.h"

#include <opencv2/opencv.hpp>

#include <QImage>

class EIRQTCV4_EXPORT cvMat : public cv::Mat
{
public:
    cvMat();
    cvMat(const cv::Mat &mat);
    cvMat(const int height, const int width, const int cvFmt);
    QImage toImage(const QImage::Format qiFormat) const;
};

