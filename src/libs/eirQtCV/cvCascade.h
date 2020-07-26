#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QSize>
#include <QString>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirExe/Configuration.h>

#include "cvMat.h"
#include "cvSize.h"

class EIRQTCV_EXPORT cvCascade
        : protected cv::CascadeClassifier
{
public:
    typedef QList<QRect> QRectList;

    class EIRQTCV_EXPORT FindParameters
    {
        FindParameters();
        void set(const Configuration &rectFindConfig);
        void calculate(const QSize inputSize,
                       const bool findAll=false);

        double scaleFactor() const;
        int minNeighbors() const;
        int flags();
        cvSize minSize() const;
        cvSize maxSize() const;
    };

public:
    cvCascade();
    ~cvCascade();
    bool isLoaded() const;
    bool notLoaded() const;
    bool load(const QFileInfo cascadeFI);
    void unload();
    QSize coreSize() const;
    bool setImage(const QImage &inputImage);
    QRectList findRects(FindParameters parms);
    QRectList findAllRects(FindParameters parms);

private:
//    cv::CascadeClassifier mCascade;
    QFileInfo mCascadeFileInfo;
    QSize mCoreSize;
    QImage mInputImage;
    QImage mFindRectImage;
    cvMat mFindRectMat;
};

