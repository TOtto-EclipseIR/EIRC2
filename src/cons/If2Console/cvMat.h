//! \file cvMat.h
#pragma once

#include <QFileInfo>

#include <opencv2/core/mat.hpp>

class cvMat
{
public:
    typedef cv::InputArray InputArray;

public:
    cvMat();
    cv::Mat mat() const;
    bool isEmpty() const;
    bool notEmpty() const;
    bool load(const QFileInfo &fileInfo);
    void set(const cv::Mat &other);
    int cols() const;
    int rows() const;

private:
    cv::Mat mCvMat;
};

