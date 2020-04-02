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
    return Var::Map::contains(name.sortable());
}

VarMap VarMap::insert(const Var &var)
{
    Var::Map::insert(var.name().sortable(), var);
//    NEEDDO("return VarMap(mVarMap)")
  //  NEEDFNR(VarMap());
    return *this;
}

Var VarMap::value(const MultiName &name) const
{
    return Var::Map::value(name.sortable());
}

VarMap VarMap::extract(const MultiName &groupName) const
{
    NEEDUSE(groupName); NEEDRTN(VarMap());
}

Var::List VarMap::values() const
{
    return Var::Map::values();
}

VarMap VarMap::operator <<  (const Var &var)
{
    return insert(var);
}

void VarMap::dump() const
{
    mName.dump();
    foreach (Var var, Var::Map::values()) var.dump();
}

