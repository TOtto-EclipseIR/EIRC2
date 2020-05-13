#include "cvInputArray.h"

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

#include <eirBase/Debug.h>

cvInputArray::cvInputArray()
{
    TRACEFN
}

void cvInputArray::clear()
{
    mMat.create(0,0,0);
    mArray = cv::_InputArray(mMat);
}

void cvInputArray::setGreyImage(const QImage &greyImage)
{
    TRACEQFI << greyImage;
    clear();
    EXPECTEQ(QImage::Format_Grayscale8, greyImage.format());
    cv::Mat greyMat(greyImage.height(),
                    greyImage.width(),
                    CV_8U,
                    (void *)greyImage.bits());
    mMat = greyMat;
    mArray = cv::_InputArray(greyMat);
    TRACE << mArray.size().height << mArray.size().width;
    EXPECTNE(0, mArray.size().area());
}

cv::Mat cvInputArray::mat() const
{
    return mMat;
}

cv::_InputArray cvInputArray::array() const
{
    return mArray;
}
