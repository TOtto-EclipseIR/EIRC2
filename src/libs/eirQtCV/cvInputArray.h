#pragma once

#include <opencv2/core/mat.hpp>

#include <QImage>

class cvInputArray : public cv::_InputArray
{
public:
    cvInputArray();
    void setGreyImage(const QImage &greyImage);
};

