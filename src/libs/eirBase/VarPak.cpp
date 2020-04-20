// file: {repo: EIRC2}./src/libs/eirBase/VarPak.cpp
#include "VarPak.h"

VarPak::VarPak(const Id id) : mId(id) {;}

Id VarPak::id() const
{
    return mId;
}

Id &VarPak::id()
{
    return mId;
}

