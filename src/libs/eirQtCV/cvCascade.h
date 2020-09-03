#pragma once
#include "eirQtCV.h"

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QPair>
#include <QSize>
#include <QString>
#include <QStringList>

#include <eirType/BasicName.h>
#include <eirType/QQFileInfo.h>
#include <eirExe/Configuration.h>
#include <eirCascade/CascadeParameters.h>
//#include <eirCascade/CascadeType.h>

#include "cvMat.h"

#include <eirBase/Typedefs.h>
#include <eirCascade/CascadeParameters.h>

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
    bool isNull() const;
    bool loadCascade(const QFileInfo &cascadeXmlInfo);
    bool notLoaded() const;
    bool isLoaded() const;
    void unload();
    QSize coreSize() const;
    QFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *cascade();

private:
    Type cmType=nullType;
    QFileInfo mCascadeXmlInfo;
    cv::CascadeClassifier *mpCascade=nullptr;
    QSize mCoreSize;

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

