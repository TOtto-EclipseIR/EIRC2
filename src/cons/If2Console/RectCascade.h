#pragma once

#include <QObject>

#include <QFileInfo>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>

#include "cvMat.h"
#include "cvRect.h"
#include "cvRectStdVector.h"
#include "cvSize.h"

typedef cv::CascadeClassifier cvCascade;

class RectCascade : public QObject
{
    Q_OBJECT
public:
    explicit RectCascade(QObject *parent = nullptr);
    bool load(const QFileInfo &fileInfo);
    QFileInfo fileInfo() const;
    QSize coreSize() const;
    void close();
    bool isEmpty() const;
    cvRectStdVector find(const cvMat &inputMat,
                      const qreal scaleFactor,
                      const int minNeighbors,
                      const cvSize minSize,
                      const cvSize maxSize);

signals:

private:
    QFileInfo mCascadeFileInfo;
    cvCascade *mpCascade=nullptr;
    QSize mCoreSize;
};

