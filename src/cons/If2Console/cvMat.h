//! \file cvMat.h
#pragma once

#include <opencv2/core/mat.hpp>

class cvMat
{
public:
    cvMat();
    bool isEmpty() const;
    void set(const cv::Mat &other);
    int cols() const;
    int rows() const;

private:
    cv::Mat mCvMat;
};

