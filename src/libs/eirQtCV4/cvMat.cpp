#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

#include <eirBase/Debug.h>

#include "cvSize.h"

#if 0
cvMat::cvMat()
{
    TRACEFN;
}

cvMat::cvMat(const cv::Mat &mat)
    : cv::Mat(mat)
{
    TRACEQFI << mat.size().height << mat.size().width
             << mat.type();
}

cvMat::cvMat(const int height, const int width, const int cvFmt)
{
    NEEDDO(cvMat ctor) NEEDUSE(height) NEEDUSE(width) NEEDUSE(cvFmt)
    //cv::Mat newMat = create(height, width, cvFmt);
}

QImage cvMat::toImage(const QImage::Format qiFormat) const
{
    TRACEQFI << qiFormat;
    cvSize cvsz(size());
    QImage image(cvsz.qSize(), QImage::Format_Grayscale8);

    switch (type())
    {
    case CV_8U:
        {
        quint8 * pDst = image.bits();
        const quint8 * pSrc = ptr(0);
        memcpy(pDst, pSrc, image.sizeInBytes());
        }
        break;

    default:
        WARN << type();
        break;
    }

    return image; // .convertTo(qiFormat);
}
#endif
