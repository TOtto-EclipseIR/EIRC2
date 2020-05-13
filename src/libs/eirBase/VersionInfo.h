#pragma once
#include "eirBase.h"

#include "VarMap.h"

class EIRBASE_EXPORT VersionInfo : public VarMap
{
public:
    VersionInfo();
    static VersionInfo version();
};

