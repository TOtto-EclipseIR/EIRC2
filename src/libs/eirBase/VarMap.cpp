#include "VarMap.h"

VarMap::VarMap(const MultiName &name) : mName(name) {;}


VarMap::VarMap(const MultiName &name, const Var::List &vars)
    : mName(name)
{
    foreach (Var var, vars) insert(var);
}

bool VarMap::contains(const MultiName &name) const
{
    return mVarMap.contains(name.sortable());
}

void VarMap::insert(const Var &var)
{
    mVarMap.insert(var.name().sortable(), var);
}

Var VarMap::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

Var::List VarMap::values() const
{
    return mVarMap.values();
}

void VarMap::operator <<(const Var &var)
{
    insert(var);
}

void VarMap::dump() const
{
    mName.dump();
    foreach (Var var, mVarMap) var.dump();
}

