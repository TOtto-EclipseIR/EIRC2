#pragma once
#include "eirQtCV.h"

#include <QImage>
#include <QSize>

namespace cv { class Mat; }

class EIRQTCV_EXPORT cvMat
{
public:
    cvMat();
    ~cvMat();
    void set(const cv::Mat other);
    void set(const QSize sz);
    void set(const QImage &qimage);
    void clear();
    cv::Mat mat() const;
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
};

