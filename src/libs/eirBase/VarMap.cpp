#include "VarMap.h"

VarMap::VarMap(const MultiName &name) : mName(name) {;}


VarMap::VarMap(const MultiName &name, const Var::List &vars)
    : mName(name)
{
    foreach (Var var, vars) insert(var);
}

void VarMap::insert(const Var &var)
{
    mVarMap.insert(var.name(), var);
}

void VarMap::operator <<(const Var &var)
{
    insert(var);
}

void VarMap::dump()
{
    mName.dump();
    foreach (Var var, mVarMap) var.dump();
}

