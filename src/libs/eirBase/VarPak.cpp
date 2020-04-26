// file: {repo: EIRC2}./src/libs/eirBase/VarPak.cpp
#include "VarPak.h"

VarPak::VarPak(const Id id) : mId(id) {;}

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

