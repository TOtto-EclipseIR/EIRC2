#pragma once

#include <eirBase/Id.h>

//#include

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

class HaarClassifier
{
public:
    HaarClassifier();

private:
    Id mId;
    cv::CascadeClassifier * mpCascade=nullptr;

};

