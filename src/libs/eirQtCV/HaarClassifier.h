// file: {repo: EIRC2}./src/libs/eirQtCV/HaarClassifier.h
#pragma once
#include "eirQtCV.h"

#include <eirBase/Id.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>


#include "ObjectType.h"

class EIRQTCV_EXPORT HaarClassifier
{
public:
    HaarClassifier();

private:
    Id mId;
    ObjectType mObjectType=ObjectType::null;
    cv::CascadeClassifier * mpCascade=nullptr;

};

