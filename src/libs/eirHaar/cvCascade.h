//! \file cvCascade.h
#pragma once
#include "eirHaar.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "cvString.h"

namespace cv { class CascadeClassifier; }
//typedef cv::CascadeClassifier cvCascadeClassifier;

//class EI#RHAAR_EXPORT cvCascade
class EIRHAAR_EXPORT cvCascade : public cv::CascadeClassifier
{
public:
    cvCascade();
    cvCascade(cvString xmlCascadeFileName);
    bool load(cvString xmlCascadeFileName);

private:
   cv::CascadeClassifier * mpCascade=nullptr;

};

