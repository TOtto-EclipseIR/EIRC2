#include "RectFinderParameters.h"

#include <eirBase/Debug.h>
#include <eirExe/ConfigObject.h>

#include "cvSize.h"

RectFinderParameters::RectFinderParameters()
{
    TRACEFN;
}

void RectFinderParameters::configure(const QSize &coreSize,
                                     const Configuration &config)
{
    mConfig = config;
    mCoreSize = coreSize;
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
    WEXPECTEQ(0, mFlags);
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
    NEEDUSE(imageSize);
    return mMinDimension;
}

int RectFinderParameters::minWidth(const QSize imageSize) const
{
    NEEDUSE(imageSize);
    return mMinWidth;
}

int RectFinderParameters::maxWidth(const QSize imageSize) const
{
    NEEDUSE(imageSize);
    return mMaxWidth;
}
