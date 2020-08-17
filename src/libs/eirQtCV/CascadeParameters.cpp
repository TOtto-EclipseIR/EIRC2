#include "CascadeParameters.h"

#include <eirXfr/Debug.h>

CascadeParameters::CascadeParameters(const Configuration &cascadeConfig)
    : mConfig(cascadeConfig)
{
    TRACEFN;
#if 1
    NEEDDO(it);
    mAll = false;
    mFactor = 1.050;
    mNeighbors = 3;
#else
    mConfig.dump();
    mAll = mConfig.boolean("FindAll", false);
    mFactor = calcFactor();
    mNeighbors = mConfig.unsignedInt("Neighbors", mAll ? 1 : 3);
#endif
}

double CascadeParameters::factor() const
{
    return mFactor;
}

int CascadeParameters::neighbors() const
{
    return mNeighbors;
}

int CascadeParameters::flags() const
{
    return mFlags;
}

qtcvSize CascadeParameters::minSize() const
{
    return mMinSize;
}

qtcvSize CascadeParameters::maxSize() const
{
    return mMaxSize;
}

Configuration CascadeParameters::cascadeConfig() const
{
    return mConfig;
}

double CascadeParameters::calcFactor()
{
    double result=1.100;
    double f = mConfig.real("Factor");
    if (f < 1.001) // calculate default
        result = mAll ? 1.050 : 1.100;
    else if (f < 2.000)
        result = f;
    else
        result = 1.000 + f / 1000.0;
    return result;
}
