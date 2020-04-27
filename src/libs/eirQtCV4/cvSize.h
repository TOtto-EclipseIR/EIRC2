#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include <QSize>

class cvSize : public cv::Size
{
public:
    cvSize();
    cvSize(const cv::Size cvsz);
    QSize qSize() const;
    operator QSize() const;
};

