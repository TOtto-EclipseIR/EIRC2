// file: {EIRC2 Repo}./src/libs/eirQtCV/HaarCascade.h
#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>

#include <eirBase/ErrorHandler.h>
#include <eirBase/Uid.h>
#include <eirBase/VarPak.h>
#include <eirType/QQRectList.h>
#include <eirQtCV/ObjectType.h>

#include "QtOpenCV.h"
#include "cvInputArray.h"

class EIRQTCV_EXPORT HaarCascade
{
public:
    HaarCascade(const ObjectType objType,
                const VarPak &config);
    ErrorHandler::Item errorItem() const;
    bool load(QFileInfo xmlFileInfo);
    bool isError() const;
    bool isLoaded() const;
    void destroy();
    Uid setImages(const QImage & inputFrame);
    void findRectangles();
    Uid uid() const;

private:
    void resetError();
    void setError(const ErrorHandler::Item &item);
    void setGreyImage();

private:
    const Uid cmUid;
    const ObjectType cmObjType=ObjectType::null;
    VarPak mConfig;
    ErrorHandler::Item mErrorItem;
    cv::CascadeClassifier * mpCascade=nullptr;
    QImage mInputImage;
    QImage mGreyImage;
    cvInputArray mGreyInput;
    cvInputArray mEqualizedInput;
    QQRectList mRectangles;
    VarPak mObjectResultMap; // for now
};
