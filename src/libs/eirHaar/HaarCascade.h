//! \file HaarCascade.h
#pragma once
#include "eirHaar.h"

#include <eirExe/FileName.h>

#include "HaarBase.h"
#include "HaarCatalog.h"


class EIRHAAR_EXPORT HaarCascade : public HaarBase
{
public:
    HaarCascade();
    HaarCascade(HaarCatalog * catalog);
    bool set(HaarCatalog * catalog);

    bool load(const FileName &xmlFileName);
    bool load(const HaarCatalog::Names &names);
    bool load(const HaarCatalog::Item &item);
    bool load(const BasicName &className); // load(default)

private:
    HaarCatalog * mpCatalog;
};

