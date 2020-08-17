#include "cvCascade.h"

//#include <opencv2/opencv.hpp>
//#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>

#include "CascadeParameters.h"
#include "cvString.h"

cvCascade::cvCascade(const CascadeType &cascadeType)
    : cmCascadeType(cascadeType)
{
    TRACEQFI << cascadeType.name() << QOBJNAME(cmpCfgObj);
}

CascadeType cvCascade::cascadeType() const
{
    return cmCascadeType;
}

const ConfigObject *cvCascade::config() const
{
    return cmpCfgObj;
}

void cvCascade::clear()
{
    mClassifier = cv::CascadeClassifier();
    mCascadeFileInfo = QFileInfo{};
    mCoreSize = QSize();
    mInputImage = QImage();
    mFindRectImage = QImage();
    mFindRectMat = cvMat();
}

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

