#include "cvSize.h"

cvSize::cvSize()
{
    width = height = 0;
}

cvSize::cvSize(const QSize qsize)
{
    width = qsize.width(),
            height = qsize.height();
}

cv::Size cvSize::operator ()() const
{
    return cv::Size(width, height);
}
