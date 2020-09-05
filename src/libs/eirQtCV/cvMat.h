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
    quint8 *data() const;
    int cols() const;
    int rows() const;
    int type() const;
    bool isNull() const;
    QSize size() const;
    void set(const cv::Mat other);
    void setGrey(const QQImage &image);
    QImage::Format qformat() const;
#if 0
    cvMat(const QString &fileName, const int imreadFlags=0);
    bool isValid() const;
    bool isGreyType() const;
    bool isGreyData() const;
    bool isGreyishData(signed epsilon=2) const;
    void set(const QSize sz);
    void set(const QImage &qimage);
    QSize toSize() const;
    QImage toImage() const;
    QPixmap toPixmap() const;
    bool imread(const QString &fileName, const int imreadFlags=0);
    bool imread(const QFileInfo &fileInfo, const int imreadFlags=0);
    bool imwrite(const QString &fileName, const IntVector parms=IntVector());
    bool imwrite(const QFileInfo &fileInfo, const IntVector parms=IntVector());
    void makeGrey(cvMat greyMat) const;
    cvMat toGrey() const;
    void markRectangles(const QList<QRect> &rectList,
                        const QColor &penColor=Qt::cyan,
                        const int penWidth=3);
#endif
    QString dumpString() const;

private:
    cv::Mat * mpCvMat=nullptr;
    QImage::Format mQFormat=QImage::Format_Invalid;
};

