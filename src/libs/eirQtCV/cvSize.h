#pragma once
#include "eirQtCV.h"

#include <QSize>

//namespace cv { class Size; }

class EIRQTCV_EXPORT cvSize
{
public:
    cvSize();
//    cvSize(const QSize qsize);
    void clear();
  //  cv::Size operator ()() const;

private:
//    cv::Size *mpCvSize=nullptr;
};

