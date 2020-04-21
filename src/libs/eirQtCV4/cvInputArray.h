#pragma once


class QImage;
namespace cv { class _InputArray; };



class cvInputArray
{
public:
    cvInputArray();
    void setGreyImage(const QImage &greyImage);

private:
    cv::_InputArray * mpArray;
};

