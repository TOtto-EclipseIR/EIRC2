#include "cvCascade.h"

#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>
#include <eirCascade/CascadeParameters.h>

#include "cvString.h"

cvCascade::cvCascade(const CascadeType &cascadeType)
    : cmCascadeType(cascadeType)
{
    TRACEQFI << cascadeType.name();
}

void cvCascade::configure(const Configuration &config)
{
    mParameters.configureCascade(config);
}

CascadeType cvCascade::cascadeType() const
{
    return cmCascadeType;
}

bool cvCascade::loadCascade(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeType().name() << cascadeXmlInfo;
    unload();
    cv::CascadeClassifier * pcvcc = new cv::CascadeClassifier;
    if (pcvcc->load(cvString(cascadeXmlInfo.absoluteFilePath())))
    {
        mpCascade = pcvcc;
        mCascadeXmlInfo = cascadeXmlInfo;
    }
    EXPECTNOT(mpCascade->empty());
    return nullptr != mpCascade;
}

bool cvCascade::notLoaded() const
{
    return mpCascade ? mpCascade->empty() : true;
}

bool cvCascade::isLoaded() const
{
    return mpCascade ? (! mpCascade->empty()) : false;
}

void cvCascade::unload()
{
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
    mCascadeXmlInfo = QFileInfo();
    mCoreSize = QSize();
}

QSize cvCascade::coreSize() const
{
    return mCoreSize;
}

QFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::cascade()
{
    return mpCascade;
}

bool cvCascade::imreadInputMat(const QQFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    mInputMat.imread(inputFileInfo.absoluteFilePath(), cv::IMREAD_COLOR);
    TRACE << mInputMat.dumpString();
    return mInputMat.isValid();
}

cvCascade::RectList cvCascade::detect()
{
    TRACEQFI << mInputMat.dumpString();
    TODO(inputSize&coreSize);
    QSize minSize = mParameters.minSize();
    QSize maxSize = mParameters.maxSize();
    cvMat detectMat(mInputMat.rows(), mInputMat.cols(), CV_8UC1);
    mInputMat.makeGrey(detectMat.mat());
    mDetectMat.set(detectMat.mat());
    std::vector<cv::Rect> cvRectVector;
    cvCascade::RectList results;

    mpCascade->detectMultiScale(detectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));

    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    mRectList = results;
    return results;
}

QString cvCascade::methodString() const
{
    return QString("Factor=%1,Neighbors=%2,%3")
            .arg(mParameters.factor()).arg(mParameters.neighbors())
            .arg(mCascadeXmlInfo.completeBaseName());
}

QString cvCascade::imwriteMarkedImage(QQFileInfo markFileInfo)
{
    TRACEQFI << markFileInfo;
    cv::Mat markMat;
    mInputMat.mat().copyTo(markMat);

    foreach (QRect qrc, mRectList)
        cv::rectangle(markMat,
                      cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()),
                      cv::Scalar(255, 255, 0),
                      3);

    markFileInfo.replace("%M", methodString());
    return  cv::imwrite(cvString(markFileInfo.absoluteFilePath()), markMat)
            ? markFileInfo.absoluteFilePath()
            : "Error writing MarkedRect file";
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

