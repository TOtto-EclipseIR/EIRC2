#include "cvCascade.h"

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

cvCascade::RectList cvCascade::detect(const cvMat &detectMat,
                                      const CascadeParameters &parms)
{
    TRACEQFI << detectMat.dumpString();
    parms.cascadeConfig().dump();
    parms.dump();
  //  QSize minSize = parms.minSize();
//    QSize maxSize = parms.maxSize();
    QSize minSize(32,32), maxSize(256,256);

    std::vector<cv::Rect> cvRectVector;
    cv::InputArray ia(detectMat.mat());
    cvCascade::RectList results;

//    cv::imshow("detectMat", detectMat.mat());
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
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

