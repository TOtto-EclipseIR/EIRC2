#pragma once
#include "eirBase.h"

#include <QMap>

#include "MultiName.h"
#include "Var.h"

class EIRBASE_EXPORT VarMap
{
public:
    VarMap(const MultiName &name=MultiName());
    VarMap(const MultiName &name,
           const Var::List & vars);
    void insert(const Var &var);
    void operator << (const Var &var);
    void dump();

private:
    MultiName mName;
    QMap<MultiName, Var> mVarMap;
};

