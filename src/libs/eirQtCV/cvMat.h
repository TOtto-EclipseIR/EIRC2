#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QPixmap>
#include <QVector>

#include <eirImage/QQImage.h>

namespace cv { class Mat; }
typedef QVector<int> IntVector;

class EIRQTCV_EXPORT cvMat
{
public:
    cvMat();
    cvMat(const int cols, const int rows, const int type);
    cvMat(const cv::Mat &otherMat);
    ~cvMat();
    void clear();
    cv::Mat mat() const;
    cv::Mat mat();
    cv::Mat operator()() const;
    size_t totalPixels() const;
    size_t depthInBytes() const;
    size_t depth() const;
    qsizetype sizeInBytes() const;
    quint8 *data() const;
    int cols() const;
    int rows() const;
    int type() const;
    bool isNull() const;
    bool isEmpty() const;
    QSize size() const;
    void set(const cv::Mat other);
    void setGrey(const QQImage &image);
    QImage::Format qformat() const;
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
    QImage::Format mQFormat=QImage::Format_Invalid;
};

