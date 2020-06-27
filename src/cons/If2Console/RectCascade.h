#pragma once

#include <QObject>

#include <QFileInfo>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>

#include "cvMat.h"
#include "cvRect.h"
#include "cvSize.h"
//#include "RectFinder.h"

typedef cv::CascadeClassifier cvCascade;

class RectCascade : public QObject
{
    Q_OBJECT
public:
    explicit RectCascade(QObject *parent = nullptr);
    bool load(const QString &fileName);
    void close();
    bool isEmpty() const;
    cvRect::Vector find(const qreal scaleFactor,
                      const int minNeighbors,
                      const cvSize minSize,
                      const cvSize maxSize);

signals:

private:
    QFileInfo mCascadeFileInfo;
    cvCascade *mpCascade=nullptr;
};

