#pragma once

#include <QFileInfo>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

//#include "D:/git/github.com/opencv/include/opencv2/opencv.hpp"

class HaarCascade
{
public:
    HaarCascade();
    bool load(const QFileInfo &xmlFileInfo);

private:
    cv::CascadeClassifier * mpCascade=nullptr;
};

