#pragma once
#include "eirQtCV.h"

#include <QSize>

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>

#include "cvCascade.h"
#include "cvMat.h"

class EIRQTCV_EXPORT CascadeParameters
{
public:
    CascadeParameters(const Configuration &cascadeConfig);
    double factor() const;
    int neighbors() const;
    int flags() const;
    QSize minSize() const;
    QSize maxSize() const;
    Configuration cascadeConfig() const;

private:
    double calcFactor(); // non-const

private:
    CascadeType mCascadeType;
    Configuration mConfig;
    bool mAll=false;
    double mFactor=1.100;
    int mNeighbors=0;
    int mFlags=0;
    QSize mMinSize;
    QSize mMaxSize;
};

