// file: {EIRC2 repo}./src/lib/eirQtCV/Detector.h
#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QFileInfo>
#include <QImage>

#include <eirBase/SetError.h>
#include <eirBase/Uid.h>
#include <eirBase/VarPak.h>
#include <eirType/QQRectList.h>

#include "cvInputArray.h"
#include "ObjectType.h"

namespace cv { class CascadeClassifier; };

class EIRQTCV_EXPORT Detector : public QObject, public SetError
{
    Q_OBJECT
public:
    explicit Detector(const ObjectType objType,
                      QObject *parent = nullptr);
    Uid uid() const;
    ObjectType objectType() const;
    bool initialize(const QFileInfo &qfiXml,
                    const VarPak &config);
    bool setImage(const QImage &image);
    bool setGreyImage(const QImage &greyImage);
    bool findRectangles(const QQRect &region=QQRect());
    QQRectList rectangles() const;

signals:

private:
    const Uid cmUid;
    const ObjectType cmObjectType = ObjectType::null;
    QFileInfo mInitFileInfo;
    VarPak mConfiguration;
    cv::CascadeClassifier * mpCascade=nullptr;
    QImage mImage;
    QImage mGreyImage;
    cvInputArray mGreyMat;
    QQRectList mRectangles;
};

