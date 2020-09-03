#include "RectangleFinder.h"

#include <eirXfr/Debug.h>

RectangleFinder::RectangleFinder(QObject *parent) : QObject(parent)
{
    MUSTDO(it);
}

void RectangleFinder::setCascadeBaseDir(const QString &cascadeBaseDirName)
{
    MUSTUSE(cascadeBaseDirName);
}

void RectangleFinder::loadCascade(const CascadeType type, const QString &cascadeXmlFileName)
{
    MUSTUSE(type); MUSTUSE(cascadeXmlFileName);
}
