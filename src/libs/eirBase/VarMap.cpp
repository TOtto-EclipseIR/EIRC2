#include "VarMap.h"

#include <eirBase/Debug.h>

VarMap::VarMap(const MultiName &name) : mName(name) {;}


VarMap::VarMap(const MultiName &name, const Var::List &vars)
    : mName(name)
{
    foreach (Var var, vars) insert(var);
}

MultiName VarMap::name() const
{
    return mName;
}

bool VarMap::contains(const MultiName &name) const
{
    return mVarMap.contains(name.sortable());
}

VarMap VarMap::insert(const Var &var)
{
    mVarMap.insert(var.name().sortable(), var);
    NEEDDO("return VarMap(mVarMap)")
    NEEDFNR(VarMap());
}

Var VarMap::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

VarMap VarMap::extract(const MultiName &groupName) const
{
    NEEDUSE(groupName); NEEDRTN(VarMap());
}

Var::List VarMap::values() const
{
    return mVarMap.values();
}

VarMap VarMap::operator <<  (const Var &var)
{
    return insert(var);
}

void VarMap::dump() const
{
    mName.dump();
    foreach (Var var, mVarMap) var.dump();
}

