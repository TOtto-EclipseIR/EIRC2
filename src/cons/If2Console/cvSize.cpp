#include "cvSize.h"

cvSize::cvSize() {;}

cvSize::cvSize(const QSize &qsize)
    : mCvSize(qsize.width(), qsize.height()) {;}

cvSize::cvSize(const cv::Size &other)
    : mCvSize(other) {;}

cvSize::operator cv::Size() const
{
    return mCvSize;
}

bool cvSize::isEmpty() const
{
    return mCvSize.empty();
}
