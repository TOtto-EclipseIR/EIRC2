#pragma once
#include "eirQtCV.h"

#include <eirBase/VarMapMap.h>

class EIRQTCV_EXPORT Configurations
{
public:
    Configurations();
    void setDefaults();
    void setOveride();
    void insert(const BasicName &name,
                const VarMap & map);

protected:
//    void insert(const Var &var,BasicName &groupName);

private:
    VarMapMap mNamedConfigMaps;

};

