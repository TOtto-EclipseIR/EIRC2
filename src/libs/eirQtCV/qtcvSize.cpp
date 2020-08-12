#include "qtcvSize.h"

qtcvSize::qtcvSize() {;}

qtcvSize::qtcvSize(const QSize qsz)
{
    width = qsz.width(), height = qsz.height();
}

void qtcvSize::set(const cv::Size cvsz)
{
    width = cvsz.width, height = cvsz.height;
}

cv::Size qtcvSize::cvsize() const
{
    return *this;
}

cv::Size qtcvSize::operator ()() const
{
    return cvsize();
}
