#pragma once
#include "eirBase.h"

#include "VarMap.h"

class EIRBASE_EXPORT VarMapMap
{
public:
    VarMapMap();
    void insert(const BasicName &name,
                const VarMap &map);
    VarMap value(const MultiName &name) const;
    bool contains(const MultiName &name) const;
    MultiName::List names() const;

private:
    VarMap::Map mNameMapMap;
};

