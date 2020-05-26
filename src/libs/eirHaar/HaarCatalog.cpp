//! \file HaarCatalog.cpp
#include "HaarCatalog.h"

#include <QFile>
#include <QDomElement>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>
#include <eirExe/XmlFile.h>

HaarCatalog::HaarCatalog(const HaarBase &haarBase)
    : HaarBase(haarBase)
{
    TRACEQFI << haarBase.baseDir();
}

HaarCatalog::HaarCatalog(const QString &baseDirPath)
    : HaarBase(baseDirPath)
{
    TRACEQFI << baseDirPath;
}

bool HaarCatalog::load(const FileName &xmlFileName)
{
    TRACEQFI << xmlFileName;
    Success success(true);
    XmlFile xmlFile(baseFileName(xmlFileName));
    success.test(xmlFile.load());
    TRACE << xmlFile.rootElement().tagName();

    return success;
}
