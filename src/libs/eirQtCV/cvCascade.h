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

#include "cvMat.h"

namespace cv { class CascadeClassifier; }
class CascadeParameters;
class ConfigObject;

class EIRQTCV_EXPORT cvCascade
{
public:
    typedef QList<QRect> QRectList;
    typedef QPair<QSize, QSize> MinMaxPair;

public:
    cvCascade(const BasicName &cascadeType,
              ConfigObject *configObject);
    ConfigObject *config() const;
    bool isLoaded() const;
    bool notLoaded() const;
    QFileInfo fileInfo() const;
    bool load(const QFileInfo cascadeFI);
    void unload();
    QSize coreSize() const;
    bool setImage(const QImage &inputImage);
    QRectList findRects();
    QImage findRectImage() const;

private:
    const BasicName cmCascadeType;
    const ConfigObject *cmpCfgObj=nullptr;
    cv::CascadeClassifier *mpCascade=nullptr;
    QFileInfo mCascadeFileInfo;
    QSize mCoreSize;
    QImage mInputImage;
    QImage mFindRectImage;
    cvMat mFindRectMat;
};

