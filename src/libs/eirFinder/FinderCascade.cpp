#include "FinderCascade.h"

#include <eirQtCV/cvCascade.h>
#include <eirQtCV/cvMat.h>
#include <eirXfr/Debug.h>

FinderCascade::FinderCascade(const CascadeType &cascadeType,
                             ConfigObject *configObject)
    : cmCascadeType(cascadeType)
    , cmpConfigObject(configObject)
{
    TRACEQFI << cascadeType.name() << QOBJNAME(configObject);
    mpCascade = new cvCascade(cascadeType);
}

const ConfigObject *FinderCascade::config() const
{
    return cmpConfigObject;
}

cvCascade *FinderCascade::cascade()
{
    return mpCascade;
}

void FinderCascade::clear()
{
    TRACEFN;
    MUSTDO(it);
}

void FinderCascade::setImage(const QImage &inputImage)
{
    TRACEQFI << inputImage.size() << inputImage.format();
    mInputImage = inputImage.convertToFormat(QImage::Format_RGB32);
    mFindRectImage = mInputImage.convertToFormat(QImage::Format_Grayscale8);
    mpFindRectMat->set(mFindRectImage);
}

int FinderCascade::findRectangles()
{
    mRectList = mpCascade->detect(*mpFindRectMat, cascadeParameters());
    return mRectList.size();
}

QList<QRect> FinderCascade::rectList() const
{
    return mRectList;
}

QImage FinderCascade::findRectImage() const
{
    return mFindRectImage;
}

Configuration FinderCascade::cascadeConfig() const
{
    Configuration result;
    NEEDDO(baseConfig)
    result += config()->
            configuration(cmCascadeType.name()+"/RectFinder");
    return result;
}

CascadeParameters FinderCascade::cascadeParameters() const
{
    NEEDDO(ImageSize); NEEDDO(coreSize);
    return CascadeParameters(cascadeConfig());
}
