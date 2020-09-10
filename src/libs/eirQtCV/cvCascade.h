#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

#include <eirBase/Typedefs.h>
#include <eirType/BasicName.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQRect.h>
#include <eirType/QQRectList.h>
#include <eirType/QQSize.h>
#include <eirExe/Configuration.h>
#include <eirImage/QQImage.h>
//#include <eirCascade/CascadeParameters.h>
//#include <eirCascade/CascadeType.h>

#include "cvMat.h"


namespace cv { class CascadeClassifier; }

class EIRQTCV_EXPORT cvCascade
{
public:
    enum Type
    {
        nullType = 0,
        PreScan, PreScanAll, Face, LeftEye, RighttEye,
        BothEyes, Nose, Mouth, LeftProfile, RightProfile,
        sizeType
    };


public:
    cvCascade(const Type &type=Type::nullType);
    Type type() const;
    BasicName typeName() const;
    bool isNull() const;
    bool loadCascade(const QFileInfo &cascadeXmlInfo);
    bool loadCoreSize(const QFileInfo &cascadeXmlInfo);
    bool notLoaded() const;
    bool isLoaded() const;
    void unload();
    QSize coreSize() const;
    QFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *classifier();

    int detectRectangles(const Configuration &rectFinderConfig,
                         const QQImage &inputImage,
                         const bool showDetect=false,
                         const QQRect &region=QQRect());
    cvMat detectMat() const;
    QQImage detectImage() const;
    QQRectList rectList() const;
    QString methodString() const;

public: // static
    static BasicName typeName(Type type);

private:
    Type cmType=nullType;
    QFileInfo mCascadeXmlInfo;
    cv::CascadeClassifier *mpClassifier=nullptr;
    QSize mCoreSize;
    // side-effects of detectRectangles()
    cvMat mDetectMat;
    QQRectList mRectList;
    QString mMethodString;

private:
    class Parameters
    {
    public:
        Parameters(const Configuration &cascadeConfig);
        void calculate(const Type type,
                       const QQSize imageSize,
                       const QQSize coreSize);
        double factor() const;
        int neighbors() const;
        int flags() const;
        QSize minSize() const;
        QSize maxSize() const;
        QString methodString(const QFileInfo &cascadeXmlInfo) const;


    private:
        double parseFactor();
        QStringList dumpList() const;

    private:
        Configuration mConfig;
        double mFactor=1.100;
        int mNeighbors=0;
        int mFlags=0;
        QQSize mMinSize;
        QQSize mMaxSize;
    };

#if 0
    void configure(const Configuration &config);
    CascadeType cascadeType() const;
    bool imreadInputMat(const QQFileInfo &inputFileInfo);
    RectList detect();
    QString methodString() const;
    bool imwriteMarkedImage(QQFileInfo markFileInfo);

private:
    bool getCoreSize(const QFileInfo &cascadeXmlInfo);
    void makeMethodString(const CascadeParameters &parms);

private:
    const CascadeType cmCascadeType;
    Configuration mCascadeConfig;
//    CascadeParameters mParameters;
    cvMat mInputMat;
    cvMat mDetectMat;
    QString mMethodString;
    RectList mRectList;
    QImage mMarkedImage;
#endif
};

typedef cvCascade::Type cvCascadeType;
