#pragma once
#include "eirExe.h"

#include <eirBase/VarMap.h>


class EIREXE_EXPORT Configuration : public VarMap
{
public:
    Configuration();
    Configuration(const VarMap &other);
};

