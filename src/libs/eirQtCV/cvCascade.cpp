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

bool cvCascade::imreadInputMat(const QFileInfo &inputFileInfo)
{
    mInputMat.imread(inputFileInfo.absoluteFilePath(), cv::IMREAD_COLOR);
    //std::cout << qPrintable(inputQMat.dumpString()) << std::endl;
    //cv::imshow("inputQMat", mInputMat.mat());
    //cv::waitKey();
/*
    mDetectMat = cvMat(mInputMat.rows(), mInputMat.cols(), CV_8UC1);
    mInputMat.makeGrey(mDetectMat);
    std::cout << qPrintable(mDetectMat.dumpString()) << std::endl;
    cv::imshow("mDetectMat", mDetectMat.mat());
    cv::waitKey();
*/
    return mInputMat.isValid();
}

cvCascade::RectList cvCascade::detect()
{
    TRACEQFI << mInputMat.dumpString();

#if 1
    cvMat detectMat(mInputMat.rows(), mInputMat.cols(), CV_8UC1);
    mInputMat.makeGrey(detectMat.mat());
    mDetectMat.set(detectMat.mat());
#else
    cvMat detectMat = mInputMat.toGrey();
#endif
    std::vector<cv::Rect> cvRectVector;
    cvCascade::RectList results;

    mpCascade->detectMultiScale(detectMat.mat(),
                        cvRectVector, 1.075, 0); /*,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));
*/
    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    mRectList = results;
    return results;
}

bool cvCascade::imwriteMarkedImage(const QFileInfo &markFileInfo)
{
    TRACEQFI << markFileInfo;
    cv::Mat markMat;
    mInputMat.mat().copyTo(markMat);
    foreach (QRect qrc, mRectList)
        cv::rectangle(markMat,
                      cv::Rect(qrc.left(), qrc.top(), qrc.width(), qrc.height()),
                      cv::Scalar(255, 255, 0),
                      0);
    return  cv::imwrite(cvString(markFileInfo.absoluteFilePath()), markMat);
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

