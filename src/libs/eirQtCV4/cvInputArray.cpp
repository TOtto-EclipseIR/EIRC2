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
    if (mpArray)
    {
        delete mpArray;
        mpArray = nullptr;
    }
}

void cvInputArray::setGreyImage(const QImage &greyImage)
{
    TRACEQFI << greyImage;
    clear();
    cv::Mat greyMat(greyImage.height(),
                    greyImage.width(),
                    CV_8U,
                    (void *)greyImage.bits());
    cv::_InputArray * pArray = new cv::_InputArray(greyMat);
    TSTALLOC(pArray);
    mpArray = pArray;
}

cv::_InputArray *cvInputArray::array() const
{
    return mpArray;
}
