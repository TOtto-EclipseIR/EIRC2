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

void RectFinder::load(const BasicName &cascadeType,
                      const QString &xmlFileName)
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

void RectFinder::configure(const Configuration &configSegment)
{
    TRACEFN;
    configSegment.dump();
    mNameConfigMap[BasicName()] = configSegment;
}

void RectFinder::configure(const BasicName &name,
                           const Configuration &configSegment)
{
    TRACEQFI << name();
    configSegment.dump();
    mNameConfigMap[name] = configSegment;
}
