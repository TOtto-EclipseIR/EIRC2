#include "cvMat.h"

#include <eirBase/Debug.h>

cvMat::cvMat()
{
    TRACEFN;
}

cvMat::cvMat(const cv::Mat &mat)
{

}

QImage cvMat::toImage(const QImage::Format qiFormat) const
{
    TRACEQFI << qiFormat;
    QImage image;
    return image;
}
