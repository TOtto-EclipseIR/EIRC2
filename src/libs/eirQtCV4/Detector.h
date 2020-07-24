// file: {EIRC2 repo}./src/lib/eirQtCV/Detector.h
#pragma once
#include "eirQtCV4.h"

#include <QObject>

#include <QFileInfo>
#include <QImage>

#include <eirType/SetError.h>
//#include <eirType/Uid.h>
#include <eirType/VarPak.h>
#include <eirType/QQRectList.h>
#include <eirType/Region.h>
#include <eirPixelImage/GreyAverageImage.h>
#include <eirPixelImage/GreyAverageImage.h>

#include "cvInputArray.h"
#include "ObjectType.h"
namespace cv { class CascadeClassifier; };

class EIRQTCV4_EXPORT Detector : public QObject, public SetError
{
    Q_OBJECT
public:
    explicit Detector(const ObjectType objType,
                      QObject *parent = nullptr);
    ObjectType objectType() const;
    bool initialize(const QFileInfo &qfiXml,
                    const VarPak &config);
    bool setImage(const QImage &image);
    bool setGreyImage(const QImage &greyImage,
                      const QFileInfo &fileInfo);
    bool findRectangles(const Region &region=Region());
    QQRectList rectangles() const;
    QImage markRectangles(const QImage frameImage,
                          const QDir &rectangleDir=QDir()) const;

signals:

private:
    const ObjectType cmObjectType = ObjectType::null;
    QFileInfo mInitFileInfo;
    VarPak mConfiguration;
    cv::CascadeClassifier * mpCascade=nullptr;
    QImage mImage;
    QImage mGreyImage;
    cvInputArray mGreyInput;
    QQRectList mRectangles;
};

