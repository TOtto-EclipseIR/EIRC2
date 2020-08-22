#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirXfr/Debug.h>

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
    TRACEQFI << qimage;
    clear();
    QSize sz = qimage.size();
    DUMPVAL(sz);
    TRACE << "new cv::Mat()" << sz.height() << sz.width()
          << ((QImage::Format_Grayscale8
             == qimage.format()) ? CV_8U : CV_8UC4);
    mpCvMat = new cv::Mat(sz.height() , sz.width(),
                    QImage::Format_Grayscale8
                        == qimage.format() ? CV_8UC1 : CV_8UC4);
    TRACE << Qt::hex << mpCvMat->data << qimage.bits() << Qt::dec
            << QString("memcpy(0x%1, 0x%2, %3*%4=%5")
             .arg("uchar*")
             .arg("uchar*")
             .arg(mpCvMat->elemSize1()).arg(mpCvMat->total())
             .arg(mpCvMat->elemSize1() * mpCvMat->total())
             ;
    std::memcpy(mpCvMat->data, qimage.bits(),
                mpCvMat->elemSize1() * mpCvMat->total());
    TRACERTV();
}

QImage cvMat::toImage() const
{
    QImage::Format f = (CV_8UC1 == mat().type()) ? QImage::Format_Grayscale8 : QImage::Format_RGB32;
    QImage image (mat().data, mat().cols, mat().rows, mat().cols, f);
    TRACEQFI << image;
    return image;
}

void cvMat::clear()
{
    TRACEFN;
    if (mpCvMat)
    {
//        TRACE << "release()" << Qt::hex << mpCvMat << Qt::dec;
  //      mpCvMat->release();
    //    TRACE << "delete" << Qt::hex << mpCvMat << Qt::dec;
      //  delete  mpCvMat;
        TRACE << "nullptr" << Qt::hex << mpCvMat << Qt::dec;
        mpCvMat = nullptr;
    }
    TRACERTV();
}

cv::Mat cvMat::mat() const
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}

QString cvMat::dumpString() const
{
    return QString("cvMat size=%1x%2 type=%3")
            .arg(mat().size().width).arg(mat().size().height)
            .arg(mat().type());
}
