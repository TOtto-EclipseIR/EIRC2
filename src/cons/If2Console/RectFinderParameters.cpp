#include "RectFinderParameters.h"

#include <eirBase/Debug.h>

#include "cvSize.h"

RectFinderParameters::RectFinderParameters(const QSize &coreSize)
    : cmCoreSize(coreSize)
{
    TRACEQFI << cmCoreSize;
}

void RectFinderParameters::configure(const QVariantMap &config)
{
    mConfig = config;
}

void RectFinderParameters::calculate(const QSize &imageSize, const QRect &regionRect)
{
    NEEDDO(it); NEEDUSE(imageSize); NEEDUSE(regionRect);
}

double RectFinderParameters::scaleFactor() const
{
    return  mScaleFactor;
}

int RectFinderParameters::minNeighbors() const
{
    return  mMinNeighbors;
}

int RectFinderParameters::flags() const
{
    WEXPECTNOT(flags());
    return mFlags;
}

cvSize RectFinderParameters::minSize() const
{
    return cvSize(mMinSize);
}

cvSize RectFinderParameters::maxSize() const
{
    return mMaxSize;
}

int RectFinderParameters::minDimension(const QSize imageSize) const
{
    return mMinDimension;
}

int RectFinderParameters::minWidth(const QSize imageSize) const
{
    return mMinWidth;
}

int RectFinderParameters::maxWidth(const QSize imageSize) const
{
    return mMaxWidth;
}
