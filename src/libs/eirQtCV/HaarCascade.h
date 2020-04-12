#pragma once

#include <QFileInfo>
#include <QImage>

#include <eirBase/ErrorHandler.h>
#include <eirBase/Uid.h>
#include <eirBase/VarMap.h>
#include <eirType/QQRect.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "QtOpenCV.h"
#include "cvInputArray.h"

class HaarCascade
{
public:
    HaarCascade(const QtOpenCV::ObjectType objType,
                const VarMap &config);
    ErrorHandler::Item errorItem() const;
    bool load(QFileInfo xmlFileInfo);
    bool isLoaded() const;
    void destroy();
    Uid setImages(const QImage & inputFrame);
    Uid uid() const;

private:
    void resetError();
    void setError(const ErrorHandler::Item &item);

private:
    const Uid mUid;
    QtOpenCV::ObjectType mObjType
        =QtOpenCV::ObjectType::nullObjectType;
    VarMap mConfig;
    ErrorHandler::Item mErrorItem;
    cv::CascadeClassifier * mpCascade=nullptr;
    QImage mInputImage;
    QImage mGreyImage;
    cvInputArray mGreyInput;
    cvInputArray mEqualizedInput;
    QQRect::List mRectangles;
    VarMap mObjectResultMap; // for now
};

