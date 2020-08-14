#include "cvCascade.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>

#include "CascadeParameters.h"
#include "cvString.h"

cvCascade::cvCascade(const BasicName &cascadeType, ConfigObject *configObject)
    : cmCascadeType(cascadeType)
    , cmpCfgObj(configObject)
{
    TRACEQFI << cascadeType() << QOBJNAME(cmpCfgObj);
}

BasicName cvCascade::cascadeType() const
{
    return cmCascadeType;
}

const ConfigObject *cvCascade::config() const
{
    return cmpCfgObj;
}

bool cvCascade::isLoaded() const
{
    return ! notLoaded();
}

bool cvCascade::notLoaded() const
{
    return mpCascade ? mpCascade->empty() : true;
}

QFileInfo cvCascade::fileInfo() const
{
    return mCascadeFileInfo;
}

bool cvCascade::load(const QFileInfo cascadeFI)
{
    TRACEQFI << cascadeFI;
    unload();
    cv::CascadeClassifier * cascade = new cv::CascadeClassifier();
    if (cascade->load(cvString(cascadeFI.filePath())))
    {
        mpCascade = cascade;
        mCascadeFileInfo = cascadeFI;
        NEEDDO(CoreSize);
    }
    return isLoaded();
}

void cvCascade::unload()
{
    TRACEQFI << mCascadeFileInfo;
    delete mpCascade;
    mpCascade=nullptr;
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

cvCascade::QRectList cvCascade::findRects()
{
    TRACEQFI << cmCascadeType();
    TSTALLOC(mpCascade);
    CascadeParameters parms(this);
    std::vector<cv::Rect> cvRectVector;
    cv::InputArray ia(mFindRectMat.mat());
    cvCascade::QRectList results;

    mpCascade->detectMultiScale(ia,
                        cvRectVector,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        parms.minSize(),
                        parms.maxSize()
                        );

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

