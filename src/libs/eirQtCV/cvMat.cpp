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
    std::memcpy(mpCvMat->ptr(), cropGreyImage.bits(),
                cropGreyImage.sizeInBytes());
    TRACERTV();
}

QImage::Format cvMat::qformat() const
{
    return mQFormat;
}

#if 0
cvMat::cvMat(const QString &fileName, const int imreadFlags)
{
    if ( ! imread(fileName, imreadFlags))
        clear();
}

bool cvMat::isValid() const
{
    if (isNull()) return false;
    // TODO more
    return true;
}

bool cvMat::isGreyType() const
{
    // note: really is single plane of unsigned char
    return 0 == type();
}

bool cvMat::isGreyData() const
{
    if (isGreyType()) return true;
    for (int r = 0; r < rows(); ++r)
    {
        quint32 *p = (quint32 *)(mat().ptr(r));
        for (int c = 0; c < cols(); ++c)
            if ( ! cvBGRA(*p++).isGrey()) return false;
    }
    return true;
}

bool cvMat::isGreyishData(signed epsilon) const
{
    if (isGreyType()) return true;
    for (int r = 0; r < rows(); ++r)
    {
        quint32 *p = (quint32 *)(mat().ptr(r));
        for (int c = 0; c < cols(); ++c)
            if ( ! cvBGRA(*p++).isGreyish(epsilon)) return false;
    }
    return true;
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

QSize cvMat::toSize() const
{
    return QSize(cols(), rows());
}

QImage cvMat::toImage() const
{
    TRACEQFI << dumpString();
    QImage::Format f = (CV_8UC1 == mat().type())
                            ? QImage::Format_Grayscale8
                            : QImage::Format_RGB32;
    QImage image;
    if (mat().isContinuous())
    {
        image = QImage(mat().data, mat().cols, mat().rows, f);
    }
    else
    {
        image = QImage(cols(), rows(), f);
        for (int r = 0; r < rows(); ++r)
            std::memcpy(image.scanLine(r), mat().ptr(r), cols() * mat().elemSize());
    }
    TRACE << image;
    return image;
}

QPixmap cvMat::toPixmap() const
{
    return QPixmap::fromImage(toImage());
}


bool cvMat::imread(const QString &fileName, const int imreadFlags)
{
    set(cv::imread(cvString(fileName), imreadFlags));
    return isValid();
}

bool cvMat::imread(const QFileInfo &fileInfo, const int imreadFlags)
{
    return imread(fileInfo.absoluteFilePath(), imreadFlags);
}

bool cvMat::imwrite(const QString &fileName, const IntVector parms)
{
    TRACEQFI << fileName;
    TODO(imwrite::params);
    return cv::imwrite(cvString(fileName), mat(),
                       std::vector<int>(parms.begin(), parms.end()));
}

bool cvMat::imwrite(const QFileInfo &fileInfo, const IntVector parms)
{
    return imwrite(fileInfo.absoluteFilePath(), parms);
}

void cvMat::makeGrey(cvMat greyMat) const
{
    TRACEQFI << greyMat.dumpString() << dumpString();
    cv::cvtColor(mat(), greyMat.mat(), cv::COLOR_BGR2GRAY);
    TRACE << greyMat.dumpString();
}

cvMat cvMat::toGrey() const
{
    TRACEQFI << dumpString();
    cv::Mat gm;
    cv::cvtColor(mat(), gm, cv::COLOR_BGR2GRAY);
    TRACE << cvMat(gm).dumpString();
    return cvMat(gm);
}

void cvMat::markRectangles(const QList<QRect> &rectList,
                           const QColor &penColor,
                           const int penWidth)
{
    cv::Scalar color(penColor.blue(), penColor.green(),
               penColor.red(), penColor.alpha());
    foreach (QRect qrc, rectList)
        cv::rectangle(mat(),
                      cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()),
                      color,
                      penWidth);
}
#endif

QString cvMat::dumpString() const
{
    return QString("cvMat size=%1x%2 type=%3 total=%4")
            .arg(mat().size().width).arg(mat().size().height)
            .arg(mat().type()).arg(mat().total());
}
