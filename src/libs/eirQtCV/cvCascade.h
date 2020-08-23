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
#include <eirExe/Configuration.h>
#include <eirCascade/CascadeType.h>

#include "cvMat.h"

namespace cv { class CascadeClassifier; }

class CascadeParameters;

class EIRQTCV_EXPORT cvCascade
{
public:
    typedef QList<QRect> RectList;

public:
    cvCascade(const CascadeType &cascadeType=CascadeType::nullCascadeType);
    CascadeType cascadeType() const;
    bool loadCascade(const QFileInfo &cascadeXmlInfo);
    bool notLoaded() const;
    bool isLoaded() const;
    void unload();
    QSize coreSize() const;
    QFileInfo cascadeFileInfo() const;
    cv::CascadeClassifier *cascade();
    RectList detect(const cvMat &detectMat,
                    const CascadeParameters &parms);

private:
    bool getCoreSize(const QFileInfo &cascadeXmlInfo);

private:
    const CascadeType cmCascadeType;
    QFileInfo mCascadeXmlInfo;
    cv::CascadeClassifier *mpCascade=nullptr;
    QSize mCoreSize;
};

