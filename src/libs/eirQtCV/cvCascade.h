#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

//#include <opencv2/opencv.hpp>
//#include <opencv2/objdetect.hpp>

#include <eirType/BasicName.h>
#include <eirExe/Configuration.h>

#include "cvMat.h"
//#include "cvSize.h"

namespace cv { class CascadeClassifier; }

class EIRQTCV_EXPORT cvCascade
{
public:
    typedef QList<QRect> QRectList;
    typedef QPair<QSize, QSize> MinMaxPair;

    class EIRQTCV_EXPORT FindParameters
    {
    public:
        enum QualityMethod
        {
            nullQualityMethod = 0,
            Tbd1 = 1,
            Tbd2 = 2,
            DefaultQualityMethod = nullQualityMethod,
            sizeQualityMethod
        };

    public:
        FindParameters();
        void set(const Configuration &rectFindConfig);
        void set(const bool findAll);
        void calculate(const QSize inputSize,
                       const QSize coreSize);

        double scaleFactor() const;
        int minNeighbors() const;
        int flags();
        MinMaxPair size() const;


    public:
        qreal mFactor=0.0;
        int mNeighbors=0;
        int mMinWidth=0;
        int mMaxWidth=0;
        int mMinHeight=0;
        int mMaxHeight=0;
        QualityMethod mQualityMethod=nullQualityMethod;
        int mMinQuality=0;
        int mMaxQuality=0;
        int mMinAcross=0;
        int mMaxAcross=0;
        int mMaxResults=0;
        bool mForce=false;
        bool mFindAll=false;
    };

public:
    cvCascade(const BasicName &cascadeType);
//    ~cvCascade();
    void dump(FindParameters parms,
              const QSize inputSize=QSize());
    bool isLoaded() const;
    bool notLoaded() const;
    QFileInfo fileInfo() const;
    bool load(const QFileInfo cascadeFI);
    void unload();
    QSize coreSize() const;
    bool setImage(const QImage &inputImage);
    QRectList findRects(FindParameters parms);
    QRectList findAllRects(FindParameters parms);

private:
    BasicName mCascadeType;
    cv::CascadeClassifier *mpCascade=nullptr;
    QFileInfo mCascadeFileInfo;
    QSize mCoreSize;
    QImage mInputImage;
    QImage mFindRectImage;
    cvMat mFindRectMat;
};

