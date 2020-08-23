#pragma once
#include "eirQtCV.h"

#include <QImage>

namespace cv { class Mat; }

class EIRQTCV_EXPORT cvMat
{
public:
    cvMat();
    cvMat(const int cols, const int rows, const int type);
    cvMat(const cv::Mat &otherMat);
    ~cvMat();
    bool imread(const QString &fileName,
                const int imreadFlags=0);
    int cols() const;
    int rows() const;
    int type() const;
    bool isNull() const;
    bool isValid() const;
    bool isGreyType() const;
    bool isGreyData() const;
    bool isGreyishData(signed epsilon=2) const;
    void set(const cv::Mat other);
    void set(const QSize sz);
    void set(const QImage &qimage);
    QImage toImage() const;
    void makeGrey(cvMat &greyMat) const;
    void clear();
    cv::Mat mat() const;
    quint8 *data() const;
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
};

