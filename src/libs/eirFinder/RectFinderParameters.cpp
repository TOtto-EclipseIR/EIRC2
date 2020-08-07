#include "RectFinderParameters.h"

#include <eirXfr/Debug.h>

RectFinderParameters::RectFinderParameters(const BasicName &cascadeType)
    : mCascadeType(cascadeType) {;}

void RectFinderParameters::configure(const Configuration finderConfig)
{
    TRACEFN;
    finderConfig.dump();
    mFactor = finderConfig.real("Factor");
    mNeighbors = finderConfig.unsignedInt("Neighbors");
    mFindAll = finderConfig.boolean("FindAll");
}

void RectFinderParameters::calculate(const QSize inputSize,
                                     const QSize coreSize)
{
    TRACEQFI << inputSize << coreSize;
    NEEDUSE(inputSize); NEEDUSE(coreSize);
    if (qIsNull(mFactor) || mFactor < 0.0)
        mDetectFactor = 1.100;
    else if (mFactor < 2.000)
        mDetectFactor = mFactor;
    else
        mDetectFactor = 1.000 + mFactor / 1000.0;

    if (mNeighbors)
        mDetectNeighbors = mNeighbors;
    else
        mDetectNeighbors = 3;
}

double RectFinderParameters::detectFactor() const
{
    return mDetectFactor;
}

int RectFinderParameters::detectNeighbors() const
{
    return mDetectNeighbors;
}
