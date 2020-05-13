#include "cvSize.h"

cvSize::cvSize() : cv::Size(0,0) {;}

cvSize::cvSize(const cv::Size cvsz) : cv::Size(cvsz) {;}

QSize cvSize::qSize() const
{
    return QSize(width, height);
}

cvSize::operator QSize() const
{
    return qSize();
}
