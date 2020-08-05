#include "cvMat.h"

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirXfr/Debug.h>

#include "cvSize.h"

cvMat::cvMat()
{
}

bool cvMat::set(const cv::Mat other)
{
    mCvMat = cv::Mat(other);
    return true;
}

void cvMat::set(const QSize sz)
{
    mCvMat.cols = sz.width(),
            mCvMat.rows = sz.height();
}

bool cvMat::set(const QImage &qimage)
{
    mCvMat.release();
    QSize sz = qimage.size();
    set(cv::Mat(sz.height() , sz.width(),
                    QImage::Format_Grayscale8
                        == qimage.format() ? CV_8U : CV_8UC4));
    std::memcpy(mCvMat.ptr(), qimage.bits(),
                mCvMat.elemSize1() * mCvMat.total());
    return true;
}

void cvMat::clear()
{
    mCvMat.release();
    NEEDDO(size_etc_ifnot_DEBUG);
}
