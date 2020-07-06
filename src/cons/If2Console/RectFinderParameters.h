#pragma once

#include <QRect>
#include <QSize>
#include <QVariantMap>

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>

#include <eirExe/ConfigObject.h>

#include "cvSize.h"
#include "RectFinderClass.h"

class RectFinderParameters
{
public:
    RectFinderParameters(const RectFinderClass &finderClass);
    void configure(const QSize &coreSize,
                   const Configuration &config);
    void calculate(const QSize &imageSize,
                   const QRect &regionRect=QRect());
    double scaleFactor() const;
    int minNeighbors() const;
    int flags() const;
    cvSize minSize() const;
    cvSize maxSize() const;

protected:
    int minDimension(const QSize imageSize) const;
    int minWidth(const QSize imageSize) const;
    int maxWidth(const QSize imageSize) const;

private:
    RectFinderClass cmClass=RectFinderClass::nullClass;
    Configuration mConfig;
    QSize mCoreSize;

    // our intermediate values
    int mMinDimension;
    int mMinWidth;
    int mMaxWidth;
    QSize mMinSize;
    QSize mMaxSize;

    // arguments to detectMultiScale()
    qreal mScaleFactor=1.1;
    int mMinNeighbors=3;
    int mFlags=0; // per OpenCV doxy 4.2.0, no longer used
    cvSize mCvMinSize;
    cvSize mCvMaxSize;
};

