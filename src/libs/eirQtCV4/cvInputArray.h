#pragma once


class QImage;

#include <opencv2/core/mat.hpp>
namespace cv { class _InputArray; };

class cvInputArray
{
public:
    cvInputArray();
    void clear();
    void setGreyImage(const QImage &greyImage);
//    cv::Mat mat() const;
  //  cv::_InputArray array() const;

private:
//    cv::Mat mMat;
  //  cv::_InputArray mArray;
};

