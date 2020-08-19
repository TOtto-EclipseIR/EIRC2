#include "cvCascade.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>

#include "CascadeParameters.h"
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

cvCascade::RectList cvCascade::detect(const cvMat &detectMat,
                                      const CascadeParameters &parms)
{
    TRACEQFI << detectMat.dumpString();
    parms.cascadeConfig().dump();
    QSize minSize = parms.minSize();
    QSize maxSize = parms.maxSize();

    std::vector<cv::Rect> cvRectVector;
    cv::InputArray ia(detectMat.mat());
    cvCascade::RectList results;

    mpCascade->detectMultiScale(ia,
                        cvRectVector,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));

    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    return results;

    return cvCascade::RectList();
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

/*
bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mClassifier.empty();
}

QFileInfo cvCascade::fileInfo() const
{
    return mCascadeFileInfo;
}

bool cvCascade::load(const QFileInfo cascadeFileInfo)
{
    TRACEQFI << cascadeFileInfo;
    unload();
    cv::CascadeClassifier cascade;
    if (cascade.load(cvString(cascadeFileInfo.filePath())))
    {
        mClassifier = cascade;
        mCascadeFileInfo = cascadeFileInfo;
        NEEDDO(CoreSize);
    }
    return isLoaded();
}

void cvCascade::unload()
{
    TRACEQFI << mCascadeFileInfo;
    mClassifier = cv::CascadeClassifier();
    mCascadeFileInfo = QFileInfo();
    mCoreSize = QSize();
    mInputImage = QImage();
    mFindRectImage = QImage();
    mFindRectMat.clear();
}

QSize cvCascade::coreSize() const
{
    return mCoreSize;
}

bool cvCascade::setImage(const QImage &inputImage)
{
    TRACEQFI << inputImage.size() << inputImage.format();
    mInputImage = inputImage;
    mFindRectImage = mInputImage.convertToFormat(QImage::Format_Grayscale8);
    mFindRectMat.set(mFindRectImage);
    return ! mInputImage.isNull();
}

cvCascade::RectList cvCascade::findRectangles()
{
    TRACEQFI << cmCascadeType();
    CascadeParameters parms(*this);
    std::vector<cv::Rect> cvRectVector;
    cv::InputArray ia(mFindRectMat.mat());
    cvCascade::RectList results;

    mClassifier.detectMultiScale(ia,
                        cvRectVector,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        parms.minSize(),
                        parms.maxSize());

    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    return results;
}

QImage cvCascade::findRectImage() const
{
    return mFindRectImage;
}

*/

