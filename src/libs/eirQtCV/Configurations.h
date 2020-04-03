#pragma once

#include <eirBase/VarMapMap.h>

class Configurations : public VarMapMap
{
public:
    Configurations();
    void setDefaults();

private:
    VarMap::Map mNamedConfigMaps;

};

