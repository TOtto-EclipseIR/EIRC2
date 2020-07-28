#include "RectFinder.h"

#include <eirXfr/Debug.h>

RectFinder::RectFinder(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
}

RectFinder::RectFinder(ConfigObject *cfgObj, QObject *parent)
{
    TRACEQFI << QOBJNAME(parent);
    mpConfogObject = cfgObj;
}

void RectFinder::set(ConfigObject *cfgObj)
{
    mpConfogObject = cfgObj;
}

bool RectFinder::contains(const BasicName &name) const
{
    return mNameCascadeMap.contains(name);
}

cvCascade *RectFinder::cascade(const BasicName &name) const
{
    return mNameCascadeMap[name];
}

void RectFinder::load(const BasicName &name, const QFileInfo &xmlFile)
{
    cvCascade * cvc = new cvCascade(name);
    if (cvc->load(xmlFile))
    {
        mNameCascadeMap[name] = cvc;
    }
}

void RectFinder::configure(const BasicName &name,
                           const Configuration &configSegment)
{
    TRACEQFI << name();
    configSegment.dump();
    NEEDUSE(name); NEEDUSE(configSegment); NEEDDO(configure);
}
