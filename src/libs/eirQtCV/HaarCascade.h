#pragma once

#include <QFileInfo>
#include <QImage>

#include <eirBase/ErrorHandler.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "QtOpenCV.h"

class HaarCascade
{
public:
    HaarCascade(const QtOpenCV::ObjectType objType,
                const VarMap &config);
    ErrorHandler::Item errorItem() const;
    bool load(QFileInfo xmlFileInfo);
    bool isLoaded() const;

private:
    void resetError();
    void setError(const ErrorHandler::Item &item);

private:
    QtOpenCV::ObjectType mObjType
        =QtOpenCV::ObjectType::nullObjectType;
    VarMap mConfig;
    ErrorHandler::Item mErrorItem;
    cv::CascadeClassifier * mpCascade=nullptr;
    QImage mInputImage;
    QImage mGreyImage;
};

