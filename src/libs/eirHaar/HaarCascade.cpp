//! \file HaarCascade.cpp
#include "HaarCascade.h"

#include <eirBase/Debug.h>

HaarCascade::HaarCascade() {;}

HaarCascade::HaarCascade(HaarCatalog *catalog)
    : mpCatalog(catalog)
{
    TRACEQFI << catalog;
}
