#pragma once

#include <QFileInfo>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "QtOpenCV.h"

class HaarCascade
{
public:
    HaarCascade(const ObjectType objType,
                const VarMap &config);
    bool load(QFileInfo xmlFileInfo);
    bool isLoaded() const;

private:
    ObjectType mObjType=ObjectType::Null;
    VarMap mConfig;
    cv::CascadeClassifier * mpCascade=nullptr;
};

