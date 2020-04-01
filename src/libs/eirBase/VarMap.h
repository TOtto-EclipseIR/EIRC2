#pragma once
#include "eirBase.h"

#include <QMap>
#include <QStack>

#include "MultiName.h"
#include "Var.h"

class EIRBASE_EXPORT VarMap
{
public:
    typedef QStack<VarMap> Stack;

public:
    VarMap(const MultiName &name=MultiName());
    VarMap(const MultiName &name,
           const Var::List & vars);
    bool contains(const MultiName & name) const;
    void insert(const Var &var);
    Var value(const MultiName & name) const;
    Var::List values() const;
    void operator << (const Var &var);
    void dump() const;

private:
    MultiName mName;
    QMap<QString, Var> mVarMap;
};

