//! \file HaarCascade.cpp
#include "HaarCascade.h"

#include <eirBase/Debug.h>

HaarCascade::HaarCascade() {;}

HaarCascade::HaarCascade(HaarCatalog *catalog)
    : mpCatalog(catalog)
{
    TRACEQFI << catalog;
}

bool HaarCascade::set(HaarCatalog *catalog)
{
    mpCatalog = catalog;
    return mpCatalog->isValid();
}

bool HaarCascade::load(const FileName &xmlFileName)
{
    TRACEQFI << xmlFileName;
    MUSTDO(load);
    return false;
}

bool HaarCascade::load(const HaarCatalog::Names &names)
{
    if (mpCatalog)
    {
        FileName xmlFileName = mpCatalog->
                cascadeXmlFile(names.className(), names.cascadeName());
        return load(xmlFileName);
    }
    return false;
}

bool HaarCascade::load(const HaarCatalog::Item &item)
{
    if (mpCatalog)
    {
        FileName xmlFileName = mpCatalog->
                cascadeXmlFile(item.className(), item.cascadeName());
        return load(xmlFileName);
    }
    return false;
}

bool HaarCascade::load(const BasicName &className)
{
    if (mpCatalog)
    {
        FileName xmlFileName = mpCatalog->defaultXmlFile(className());
        return load(xmlFileName);
    }
    return false;
}
