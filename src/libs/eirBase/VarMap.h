#pragma once
#include "eirBase.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "MultiName.h"
#include "Var.h"

class EIRBASE_EXPORT VarMap
{
public:
    typedef QList<VarMap> List;
    typedef QStack<VarMap> Stack;

public:
    VarMap(const MultiName &name=MultiName());
    VarMap(const MultiName &name,
           const Var::List & vars);
    MultiName name() const;
    bool contains(const MultiName & name) const;
    VarMap insert(const Var &var);
    Var value(const MultiName & name) const;
    VarMap extract(const MultiName & groupName) const;
    Var::List values() const;
    VarMap operator << (const Var &var);
    void dump() const;

private:
    MultiName mName;
    QMap<QString, Var> mVarMap;
};

