//! \file cvCascade.h
#pragma once
#include "eirHaar.h"

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "cvString.h"

class EIRHAAR_EXPORT cvCascade
{
public:
    cvCascade();
    bool load(cvString xmlCascadeFileName);

private:
   cv::CascadeClassifier * mpCascade=nullptr;

};

