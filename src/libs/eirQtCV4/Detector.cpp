// file: {EIRC2 repo}./src/lib/eirQtCV/Detector.h
#include "Detector.h"

#include <QRect>
#include <QVector>

#include <vector> // std

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect.hpp>

#include <eirXfr/Debug.h>
#include <eirType/Success.h>
#include <eirPixelImage/ImageMarker.h>
#include <eirXfr/HexDump.h>

#include "cvMat.h"
#include "cvRect.h"
#include "cvString.h"

#if 0

Detector::Detector(const ObjectType objType, QObject *parent)
    : QObject(parent)
    , cmObjectType(objType)
{
    TRACEQFI << objType.name()
             << (parent ? parent->objectName() : "{null parent}");
    setObjectName("Detector:" + objType.name());
    WANTDO(Implement asynch slot/signals);
}

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

bool Detector::setGreyImage(const QImage &greyImage,
                            const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo << greyImage;
    mInitFileInfo = fileInfo;
    Success success(true);
    if (QImage::Format_Grayscale8 != greyImage.format())
    {
        GreyAverageImage gaImage;
        gaImage.create(greyImage);
        EXPECT(gaImage.isGrey())
    }
    EXPECT(success.test(greyImage.isGrayscale()));
    mGreyImage = greyImage;
    TRACEFNR(success);
}

bool Detector::findRectangles(const Region &region)
{
    TRACEQFI << region;
    Success success(true);
    TSTALLOC(mpCascade)
    EXPECTNOT(success.testNot(mGreyImage.isNull()))
    EXPECT(success.test(mGreyImage.isGrayscale()))
    std::vector<cv::Rect> outputVector;
    mRectangles.clear();
    WANTDO(region)
    mGreyInput.setGreyImage(mGreyImage);
    mpCascade->detectMultiScale(mGreyInput.mat(),
                                outputVector, // rectList
                                1.10,        // factor
                                0,          // neighbors
                                0,      // flags
                                cv::Size(),     // minSize
                                cv::Size());    // maxSize
    TRACE << outputVector.size() << "rectangles";
    foreach(cv::Rect rc, outputVector)
        mRectangles << QQRect(cvRect(rc));
    TRACE << mRectangles.size();
    TRACEQFI << "return" << success.toString();
    return success;
}

QQRectList Detector::rectangles() const
{
    return mRectangles;
}

QImage Detector::markRectangles(const QImage frameImage,
                                const QDir &rectangleDir) const
{
    TRACEQFI << rectangleDir;
    QImage rectImage = frameImage;
    ImageMarker marker(rectImage);
    marker.markRectangles(rectangles());
    if (rectangleDir != QDir())
    {
        QFileInfo qfi(rectangleDir,
                       mInitFileInfo.fileName());
        TRACE << qfi;
        WEXPECT(marker.marked().save(qfi.filePath()));
    }
    return marker.marked();
}
#endif
