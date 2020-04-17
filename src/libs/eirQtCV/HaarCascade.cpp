// file: {EIRC2 Repo}./src/libs/eirQtCV/HaarCascade.cpp
#include "HaarCascade.h"

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>

#include "cvString.h"
#include "ObjectType.h"

HaarCascade::HaarCascade(const ObjectType objType,
                         const VarPak &config)
    : cmUid(Uid::create())
    , cmObjType(objType)
    , mConfig(config) { TRACEFN; }

ErrorHandler::Item HaarCascade::errorItem() const
{
    return mErrorItem;
}

bool HaarCascade::load(QFileInfo xmlFileInfo=QFileInfo())
{
    TRACEQFI << xmlFileInfo << cmObjType;
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
#if 1
    NEEDDO(It Right!)
    xmlFileInfo = QFileInfo(QDir("../Detectors"),
                            "DefaultFrontalFace.xml");
#else
    if ( ! xmlFileInfo.isFile())
        xmlFileInfo = QFileInfo(
                QDir(mConfig.value("DetectorDir")
                    .current().toString()),
                mConfig.value("FileName")
                    .current().toString());
#endif
    TRACEQFI << xmlFileInfo;
    if ( ! errorHandler()->tryFileMode(QIODevice::ReadOnly,
                                xmlFileInfo,
                                "HaarCascade XML file"))
        return false;
    cv::CascadeClassifier * cascade = new cv::CascadeClassifier();
    TSTALLOC(cascade);
    if ( ! errorHandler()->
         expect(cascade->load(cvString(xmlFileInfo.filePath())),
                "Loading HaarCascadeClassifier: "
                + xmlFileInfo.filePath()))
        return false;
    mpCascade = cascade;
    return true;
}

bool HaarCascade::isError() const
{
    return ! mErrorItem.isNull();
}

void HaarCascade::destroy()
{
    TRACEQFI << cmObjType;
    if (mpCascade) delete mpCascade;
}

Uid HaarCascade::setImages(const QImage &inputFrame)
{
    TRACEQFI << cmObjType << inputFrame;
    mInputImage = inputFrame;
    setGreyImage();
    mGreyInput.setGreyImage(mGreyImage);
    return cmUid;
}

void HaarCascade::findRectangles()
{
    TRACEFN
    TSTALLOC(mpCascade);

    std::vector<cv::Rect> rects;
    mpCascade->detectMultiScale(mGreyInput, rects, 1.1, 1);

    QVector<cv::Rect> qvrect
            = QVector<cv::Rect>::fromStdVector(rects);
    foreach (cv::Rect cvrect, rects)
    {
        int x = cvrect.x;
        int y = cvrect.y;
        int width = cvrect.width;
        int height = cvrect.height;
        QQRect qqr(x, y, width, height);
        mRectangles.append(qqr);
    }
}

Uid HaarCascade::uid() const
{
    return cmUid;
}

void HaarCascade::resetError()
{
    mErrorItem = ErrorHandler::Item();
}

void HaarCascade::setError(const ErrorHandler::Item &item)
{
    mErrorItem = item;
}

void HaarCascade::setGreyImage()
{
    TRACEQFI << cmObjType << mInputImage;
    QImage grey(mInputImage.size(), QImage::Format_Indexed8);
    QVector<QRgb> greyColorTable(256);
    for (unsigned char b = 0; b < 255; ++b)
        greyColorTable[b] = qRgb(b,b,b);
    grey.setColorTable(greyColorTable);
    for (int row = 0; row < mInputImage.size().height(); ++row)
        for (int col = 0; col < mInputImage.size().width(); ++col)
            grey.setPixel(col, row,
                qGray(mInputImage.pixel(col, row)));
    mGreyImage = grey;
}
