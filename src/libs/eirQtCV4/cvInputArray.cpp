#include "cvInputArray.h"

#include <QImage>

#ifndef STUB_OPENCV4
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#endif
#include <eirBase/Debug.h>

cvInputArray::cvInputArray()
{
    TRACEFN
}

void cvInputArray::setGreyImage(const QImage &greyImage)
{
    TRACEQFI << greyImage;
#ifdef STUB_OPENCV
    WANTDO(setGreyImage)
#else
    cv::Mat greyMat(greyImage.height(),
                   greyImage.width(),
                    CV_8U,
                    (void *)greyImage.bits());
    int n = greyImage.byteCount();
    quint8 * pSource;
    WANTDO(pDest);
    WANTDO(memcpy);
    WANTDO(alloc mpArray)
#endif
}
