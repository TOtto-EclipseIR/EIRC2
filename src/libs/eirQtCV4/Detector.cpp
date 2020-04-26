// file: {EIRC2 repo}./src/lib/eirQtCV/Detector.h
#include "Detector.h"

#include <QRect>
#include <QVector>

#include <vector> // std

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>
#include <eirPixelImage/ImageMarker.h>

#include "cvRect.h"
#include "cvString.h"


Detector::Detector(const ObjectType objType, QObject *parent)
    : QObject(parent)
//    , cmUid(Uid::create())
    , cmObjectType(objType)
{
    TRACEQFI << objType.name()
             << (parent ? parent->objectName() : "{null parent}");
    setObjectName("Detector:" + objType.name());
    WANTDO(Implement asynch slot/signals);
}
/*
Uid Detector::uid() const
{
    return cmUid;
}
*/
ObjectType Detector::objectType() const
{
    return cmObjectType;
}

bool Detector::initialize(const QFileInfo &qfiXml,
                          const VarPak &config)
{
    TRACEQFI << qfiXml << config.id().name()();
    mConfiguration = config;

    mpCascade = new cv::CascadeClassifier();
    WANTDO(Refactor ErrorHandler::tryFileMode())
    if (nullptr == mpCascade)
    {

        ErrorHandler::Item ei("eirQtCV/Detector/CtorCascade");
        setError(ei);
        return false;
    }
    if ( ! mpCascade->load(cvString(qfiXml.filePath())))
    {
        VarMap vars;
        vars.insert(Var("FilePath", qfiXml.absoluteFilePath()));
        ErrorHandler::Item ei("eirQtCV/Detector/CascadeLoad", vars);
        setError(ei);
        return false;
    }
    TODO(More?)
    return true;
}

bool Detector::setGreyImage(const QImage &greyImage)
{
    TRACEQFI << greyImage;
    Success success(true);
    WEXPECT(success.test(greyImage.isGrayscale()));
    mGreyImage = greyImage;
    mGreyMat.setGreyImage(mGreyImage);
    return success;
}

bool Detector::findRectangles(const QQRect &region)
{
    TRACEQFI << region;
    Success succcess(true);
    TSTALLOC(mpCascade)
    WEXPECTNOT(succcess.test(mGreyImage.isNull()))
    WEXPECTNOT(succcess.test(mGreyImage.isGrayscale()))
    std::vector<cv::Rect> outputVector;
    mRectangles.clear();

    mpCascade->detectMultiScale(*mGreyMat.array(),
                                outputVector, // rectList
                                1.1,        // factor
                                1,          // neighbors
                                0,      // flags
                                cv::Size(),     // minSize
                                cv::Size());    // maxSize
    foreach(cv::Rect rc, outputVector)
        mRectangles << QQRect(cvRect(rc));

    return succcess;
}

QQRectList Detector::rectangles() const
{
    return mRectangles;
}

QImage Detector::markRectangles(const bool inLivingColor,
                                const QDir &rectangleDir) const
{
    TRACEQFI << rectangleDir;
    QImage rectImage = inLivingColor? mImage : mGreyImage;
    ImageMarker marker(rectImage);
    marker.markRectangles(rectangles());
    if (rectangleDir != QDir())
        marker.marked().save(QFileInfo(rectangleDir,
                    mInitFileInfo.fileName()).filePath());
    return marker.marked();
}
