#include "cvMat.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

#include <eirType/QQRect.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

#include "cvBGRA.h"
#include "cvString.h"

cvMat::cvMat() {;}

cvMat::cvMat(const int rows, const int cols, const int type)
{
    TRACEQFI << rows << cols << type;
    mpCvMat = new cv::Mat(rows, cols, type);
    //EXPECT(isValid());
    TRACE << dumpString();
}

cvMat::cvMat(const cv::Mat &otherMat)
{
    set(otherMat);
}

cvMat::~cvMat()
{
    clear();
}

void cvMat::clear()
{
    TRACEFN;
    if (mpCvMat)
    {
        TRACE << "release()" << Qt::hex << mpCvMat << Qt::dec;
        mpCvMat->release();
        TRACE << "delete" << Qt::hex << mpCvMat << Qt::dec;
        delete mpCvMat;
        TRACE << "nullptr" << Qt::hex << mpCvMat << Qt::dec;
        mpCvMat = nullptr;
    }
    TRACERTV();
}

cv::Mat cvMat::mat() const
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}

cv::Mat cvMat::mat()
{
    return  mpCvMat ? *mpCvMat : cv::Mat();
}

cv::Mat cvMat::operator()() const
{
    return mat();
}

size_t cvMat::totalPixels() const
{
    return mat().total();
}

size_t cvMat::depthInBytes() const
{
    return mat().elemSize();
}

size_t cvMat::depth() const
{
    return depthInBytes() * 8;
}

qsizetype cvMat::sizeInBytes() const
{
    return totalPixels() * depthInBytes();
}

quint8 *cvMat::data() const
{
    return mat().data;
}

int cvMat::cols() const
{
    return mat().cols;
}

int cvMat::rows() const
{
    return mat().rows;
}

int cvMat::type() const
{
    return mat().type();
}

bool cvMat::isNull() const
{
    return mat().rows <= 0 || mat().cols <= 0 || nullptr == data();
}

bool cvMat::isEmpty() const
{
    return mat().empty();
}

QSize cvMat::size() const
{
    return QSize(cols(), rows());
}

void cvMat::set(const cv::Mat other)
{
    mpCvMat = new cv::Mat(other);
}

void cvMat::setGrey(const QQImage &image)
{
    TRACEQFI << image;
    EXPECTNOT(image.isNull());
    if (image.isNull()) return;                             /* /=========\ */
    QQImage greyImage = image.convertToFormat(QImage::Format_Grayscale8);
    QPoint cropCenter = greyImage.rect().center();
    QQSize cropSize(greyImage.cols(), greyImage.rows(), 16);
    QQRect cropRect(cropSize, cropCenter);
    QQImage cropGreyImage = greyImage.copy(cropRect);
    EXPECTEQ(1, cropGreyImage.depth());
    EXPECTEQ(cropSize.area(), cropGreyImage.sizeInBytes());
    clear();
    mpCvMat = new cv::Mat(image.height(), image.width(), CV_8UC1);
    TSTALLOC(mpCvMat->ptr());
    EXPECTEQ(cropGreyImage.depth(), int(mpCvMat->elemSize1()));
    EXPECTEQ(cropGreyImage.sizeInBytes(), int(mpCvMat->total()));
//  std::memcpy(mpCvMat->ptr(), cropGreyImage.bits(), sizeInBytes());
    std::memcpy(mpCvMat->ptr(), cropGreyImage.bits(), cropGreyImage.sizeInBytes());
    mQFormat = QImage::Format_Grayscale8;
    TRACERTV();
}

QImage::Format cvMat::qformat() const
{
    return mQFormat;
}

QString cvMat::dumpString() const
{
    return QString("cvMat size=%1x%2 type=%3 total=%4")
            .arg(mat().size().width).arg(mat().size().height)
            .arg(mat().type()).arg(sizeInBytes());
}
