#include "cvInputArray.h"

cvInputArray::cvInputArray()
{

}

void cvInputArray::setGreyImage(const QImage &greyImage)
{
    cv::Mat greyMat(greyImage.height(),
                   greyImage.width(),
                    CV_8U,
                    (void *)greyImage.bits());
}
