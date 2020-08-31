#include "CascadeParameters.h"

#include <eirXfr/Debug.h>

CascadeParameters::CascadeParameters(const Configuration &cascadeConfig)
    : mConfig(cascadeConfig)
{
    TRACEFN;
    NEEDDO(ImageSize); NEEDDO(coreSize);
    mConfig.setName("CascadeConfiguration");
    mConfig.dump();
#if 0
    NEEDDO(it);
    mAll = true;
    mFactor = 1.010;
    mNeighbors = 0;
#else
    mAll = mConfig.boolean("FindAll", false);
    mFactor = calcFactor();
    mNeighbors = mConfig.unsignedInt("Neighbors", mAll ? 1 : 3);
#endif
}

CascadeParameters::CascadeParameters(const double factor, const int neighbors)
    : mFactor(factor), mNeighbors(neighbors) {;}

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

QSize CascadeParameters::minSize() const
{
    return ! mMinSize.isValid() ? QSize(0,0) : mMinSize;
}

QSize CascadeParameters::maxSize() const
{
    return ! mMaxSize.isValid() ? QSize(0,0) : mMaxSize;
}

Configuration CascadeParameters::cascadeConfig() const
{
    return mConfig;
}

QStringList CascadeParameters::dumpList() const
{
    QStringList qsl;
    qsl << QString("%1 = %2").arg("mAll").arg(mAll);
    qsl << QString("%1 = %2").arg("factor").arg(factor());
    qsl << QString("%1 = %2").arg("mNeighbors").arg(neighbors());
    qsl << QString("%1 = %2").arg("mFlags").arg(flags());
    qsl << QString("%1 = %2x%3").arg("mMinSize").arg(minSize().width()).arg(minSize().height());
    qsl << QString("%1 = %2x%3").arg("mMaxSize").arg(maxSize().width()).arg(maxSize().height());
    return qsl;
}

void CascadeParameters::dump() const
{
    DUMP << dumpList();
}

double CascadeParameters::calcFactor()
{
    TRACEFN;
    double result=1.100;
    double f = mConfig.real("Factor");
    if (f < 1.001) // calculate default
        result = mAll ? 1.075 : 1.150;
    else if (f < 2.000)
        result = f;
    else
        result = 1.000 + f / 1000.0;
    TRACE << f << result;
    return result;
}

void CascadeParameters::configureCascade(const Configuration &cascadeConfig)
{
    TRACEFN;
    mConfig += cascadeConfig;
    mConfig.dump();
}
