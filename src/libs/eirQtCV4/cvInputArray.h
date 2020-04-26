#pragma once


class QImage;
namespace cv { class _InputArray; };



class cvInputArray
{
public:
    cvInputArray();
    void clear();
    void setGreyImage(const QImage &greyImage);
    cv::_InputArray * array() const;

private:
    cv::_InputArray * mpArray=nullptr;
};

