//! \file cvMat.cpp
#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <eirBase/Debug.h>

cvMat::cvMat() {;}

cv::Mat cvMat::mat() const
{
    return mCvMat;
}

bool cvMat::isEmpty() const
{
    return mCvMat.empty();
}

bool cvMat::notEmpty() const
{
    return ! isEmpty();
}

bool cvMat::load(const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo.absoluteFilePath();
    set(cv::imread(fileInfo.absoluteFilePath().toStdString()));
    WANTDO(isValid());
    return notEmpty();
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
