//! \file HaarCascade.h
#pragma once
#include "eirHaar.h"

#include <eirExe/FileName.h>

#include "HaarCatalog.h"

class EIRHAAR_EXPORT HaarCascade
{
public:
    HaarCascade();
    HaarCascade(HaarCatalog * catalog);
    bool load(const FileName &xmlFileName);
    bool load(const HaarCatalog::Names &names);
    bool load(const HaarCatalog::Item &item);

private:
    HaarCatalog * mpCatalog;
};

