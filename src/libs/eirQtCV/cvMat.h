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
    bool isNull() const;
    bool isValid() const;
    void set(const cv::Mat other);
    void set(const QSize sz);
    void set(const QImage &qimage);
    QImage toImage() const;
    void clear();
    cv::Mat mat() const;
    quint8 *data() const;
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
};

