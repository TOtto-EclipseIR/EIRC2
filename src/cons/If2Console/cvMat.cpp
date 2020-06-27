//! \file cvMat.cpp
#include "cvMat.h"

cvMat::cvMat() {;}

bool cvMat::isEmpty() const
{
    return mCvMat.empty();
}

void cvMat::set(const cv::Mat &other)
{
    mCvMat = other;
}

int cvMat::cols() const
{
    return mCvMat.cols;
}

int cvMat::rows() const
{
    return mCvMat.rows;
}
