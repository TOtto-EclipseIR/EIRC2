// file: {repo: EIRC2}./src/libs/eirBase/VarPak.cpp
#include "VarPak.h"

VarPak::VarPak(const Id id) : mId(id) {;}

void VarPak::insert(const VarMap &varMap)
{
    mVarMap.insert(varMap);
}

void VarPak::insert(const Var &mapItem)
{
    mVarMap.insert(mapItem);
}

void VarPak::insert(const MultiName &key, const QVariant &value)
{
    insert(Var(key, value));
}

Var &VarPak::at(const MultiName &name)
{
    return mVarMap.at(name);
}

Var VarPak::var(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

QVariant VarPak::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable()).value();
}

Id VarPak::id() const
{
    return mId;
}

Id &VarPak::id()
{
    return mId;
}

