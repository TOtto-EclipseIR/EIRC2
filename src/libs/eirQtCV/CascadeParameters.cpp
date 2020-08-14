#include "CascadeParameters.h"

#include <eirXfr/Debug.h>

CascadeParameters::CascadeParameters(const BasicName &cascadeType,
                                     const ConfigObject *cfgObj,
                                     const QImage &image,
                                     cvCascade *cascade)
    : cmpCfgObj(cfgObj)
    , mCascadeType(cascadeType)
    , mpCascade(cascade)

{
    TSTALLOC(cascade);
    TSTALLOC(cfgObj);
    TRACEQFI << image.format() << image.size()
             << cascade->fileInfo();
    mConfig = cfgObj->configuration("Option/RectFinder");
    mConfig += cfgObj->configuration(mCascadeType + "/RectFinder");
    mConfig.dump();
    mAll = mConfig.boolean("FindAll");;
    QImage greyImage = image.convertToFormat(QImage::Format_Grayscale8);
    mCvMat.set(greyImage);
    mFactor = factor();
    mNeighbors = mConfig.unsignedInt("Neighbors", mAll ? 1 : 3);
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
