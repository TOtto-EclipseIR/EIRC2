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
    mInputImage = mFindRectImage = QImage();
    mFindRectMat.clear();
}

QSize cvCascade::coreSize() const
{
    return mCoreSize;
}

bool cvCascade::setImage(const QImage &inputImage)
{
    TRACEQFI << inputImage.size() << inputImage.format();
    MUSTDO(it); MUSTDO(mFindRectImage);
    MUSTDO(mFindRectMat); MUSTUSE(inputImage);
    MUSTRTN(false);
    return false;
}

cvCascade::QRectList cvCascade::findRects()
{
    TRACEQFI << cmCascadeType();
    TSTALLOC(mpCascade);
    CascadeParameters parms(cmCascadeType,
                            cmpCfgObj,
                            mInputImage,
                            this);
    std::vector<cv::Rect> cvRectVector;
    cv::InputArray ia(parms.detectMat().mat());
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


    /*
    Classifier::detectMultiScale(
    InputArray 	image,
    std::vector< Rect > & 	objects,
    double 	scaleFactor = 1.1,
    int 	minNeighbors = 3,
    int 	flags = 0,
    Size 	minSize = Size(),
    Size 	maxSize = Size()
    )
    */

QImage cvCascade::findRectImage() const
{
    return mFindRectImage;
}

