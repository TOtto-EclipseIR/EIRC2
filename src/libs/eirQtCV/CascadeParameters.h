#pragma once
#include "eirQtCV.h"

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>

#include "cvCascade.h"
#include "cvMat.h"
#include "qtcvSize.h"

class EIRQTCV_EXPORT CascadeParameters
{
public:
    CascadeParameters(const BasicName &cascadeType,
                      ConfigObject *cfgObj,
                      const QImage &image,
                      cvCascade *cascade);
    cvMat detectMat() const;
    double factor() const;
    int neighbors() const;
    int flags() const;
    qtcvSize minSize() const;
    qtcvSize maxSize() const;

private:
    double factor(); // non-const


private:
    ConfigObject *mpCfgObj=nullptr;
    BasicName mCascadeType;
    Configuration mConfig;
    bool mAll=false;
    cvMat mCvMat;
    cvCascade *mpCascade=nullptr;
    double mFactor=1.100;
    int mNeighbors=0;
    int mFlags=0;
    qtcvSize mMinSize;
    qtcvSize mMaxSize;
};

