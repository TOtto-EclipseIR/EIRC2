#pragma once

#include <QSize>

#include <eirType/BasicName.h>
#include <eirType/MinMaxTPair.h>
#include <eirType/Var.h>
#include <eirExe/Configuration.h>

typedef MinMaxPair<QSize> MinMaxSizePair;

class RectFinderParameters
{
public:
    RectFinderParameters(const BasicName &cascadeType);
    void configure(const Configuration finderConfig);
    void calculate(const QSize inputSize,
                   const QSize coreSize);
    double detectFactor() const;
    int detectNeighbors() const;

private:
    BasicName mCascadeType;

    // configuration
    qreal mFactor=0.0;
    int mNeighbors=0;
    bool mFindAll=false;

    // calculated parameters
    double mDetectFactor=0.0;
    int mDetectNeighbors=0;
};

