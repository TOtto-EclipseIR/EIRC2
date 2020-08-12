#include "RectFinder.h"

#include <eirXfr/Debug.h>

RectFinder::RectFinder(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
}

RectFinder::RectFinder(ConfigObject *cfgObj,
                       QObject *parent)
{
    TRACEQFI << QOBJNAME(parent);
    mpConfigObject = cfgObj;
}

void RectFinder::set(ConfigObject *cfgObj)
{
    mpConfigObject = cfgObj;
}

void RectFinder::set(const QDir &baseDir)
{
    mBaseDir = baseDir;
}

bool RectFinder::loaded(const BasicName &cascadeType) const
{
    return mNameCascadeMap.contains(cascadeType);
}

cvCascade *RectFinder::cascade(const BasicName &cascadeType) const
{
    return mNameCascadeMap[cascadeType];
}

QImage RectFinder::findRectImage(const BasicName &cascadeType) const
{
    TRACEQFI << cascadeType();
    return cascade(cascadeType)->findRectImage();
}

QQRectList RectFinder::rectangleList(BasicName cascadeType)
{
    return mNameRectListMap.value(cascadeType);
}

void RectFinder::load(BasicName cascadeType,
                      QString xmlFileName)
{
    TRACEQFI << cascadeType() << xmlFileName;
    cvCascade * cvc = new cvCascade(cascadeType);
    QFileInfo xmlFileInfo(mBaseDir, xmlFileName);
    NEEDDO(exists-readable);
    TRACE << xmlFileInfo << xmlFileInfo.exists()
          << xmlFileInfo.isReadable();
    if (cvc->load(xmlFileInfo.filePath()))
    {
        mNameCascadeMap[cascadeType] = cvc;
    }
}

void RectFinder::configure(Configuration baseConfig)
{
    TRACEFN;
    baseConfig.dump();
    mNameConfigMap[BasicName()] = baseConfig;
}

void RectFinder::configure(BasicName cascadeType,
                           Configuration cascadeConfig)
{
    TRACEQFI << cascadeType();
    cascadeConfig.dump();
    mNameConfigMap[cascadeType] = cascadeConfig;
}

void RectFinder::set(QImage image)
{
    TRACEQFI << image.size() << image.format();
    NEEDDO(it); NEEDUSE(image);
}

void RectFinder::findRectangles(BasicName cascadeType)
{
    TRACEQFI << cascadeType();
    NEEDDO(it); NEEDUSE(cascadeType);
}
