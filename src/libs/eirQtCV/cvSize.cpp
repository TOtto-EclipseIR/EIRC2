#include "cvSize.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>

cvSize::cvSize()
{
    clear();
}
/*
cvSize::cvSize(const QSize qsize)
{
    mpCvSize = new cv::Size(qsize.width(), qsize.height());
}
*/
void cvSize::clear()
{
    /*
    if (mpCvSize)
    {
        delete mpCvSize;
        mpCvSize = nullptr;
    }
    */
}
/*
cv::Size cvSize::operator ()() const
{
    return mpCvSize ? *mpCvSize : cv::Size();
}
*/
