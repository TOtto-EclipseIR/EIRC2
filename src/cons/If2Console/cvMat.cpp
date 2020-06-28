//! \file cvMat.cpp
#include "cvMat.h"

#include <QTemporaryFile>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <eirBase/Debug.h>

cvMat::cvMat() {;}

cv::Mat cvMat::mat() const
{
    return mCvMat;
}

bool cvMat::isEmpty() const
{
    return mCvMat.empty();
}

bool cvMat::notEmpty() const
{
    return ! isEmpty();
}

bool cvMat::load(const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo.absoluteFilePath();
    set(cv::imread(fileInfo.absoluteFilePath().toStdString()));
    WANTDO(isValid());
    return notEmpty();
}

void cvMat::set(const cv::Mat &other)
{
    mCvMat = other;
}

QImage cvMat::toImage(const QImage::Format qFormat, const QByteArray &mimeFormat)
{
    TRACEQFI << qFormat << mimeFormat;
    QTemporaryFile imwriteFile("imwrite" + mimeFormat);
    EXPECT(imwriteFile.open());
    QString imwriteTempFilePath = imwriteFile.fileName();
    EXPECTNOT(imwriteTempFilePath.isEmpty());
    imwriteFile.close();
    EXPECT(cv::imwrite(imwriteTempFilePath.toStdString(), mat()));
    QImage imwriteImage(imwriteTempFilePath);
    QImage resultImage = imwriteImage.convertToFormat(qFormat);
    WEXPECTNOT(resultImage.isNull());
    return resultImage;
}

int cvMat::cols() const
{
    return mCvMat.cols;
}

int cvMat::rows() const
{
    return mCvMat.rows;
}
