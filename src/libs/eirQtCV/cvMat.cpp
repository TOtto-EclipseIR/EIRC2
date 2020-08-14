#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirXfr/Debug.h>

#include "del-cvSize.h"

cvMat::cvMat() {;}

cvMat::~cvMat()
{
    clear();
}

void cvMat::set(const cv::Mat other)
{
    mpCvMat = new cv::Mat(other);
}

void cvMat::set(const QSize sz)
{
    mpCvMat = new cv::Mat();
    mpCvMat->cols = sz.width(),
            mpCvMat->rows = sz.height();
}

void cvMat::set(const QImage &qimage)
{
    clear();
    QSize sz = qimage.size();
    mpCvMat = new cv::Mat(sz.height() , sz.width(),
                    QImage::Format_Grayscale8
                        == qimage.format() ? CV_8U : CV_8UC4);
    std::memcpy(mpCvMat->data, qimage.bits(),
                mpCvMat->elemSize1() * mpCvMat->total());
}

void cvMat::clear()
{
    if (mpCvMat)
    {
        mpCvMat->release();
        delete  mpCvMat;
        mpCvMat = nullptr;
    }
}

cv::Mat cvMat::mat() const
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}
