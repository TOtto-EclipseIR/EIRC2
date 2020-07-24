// file: {EIRC2 repo}./src/libs/eirType/MultiNameMap.cpp
#include "MultiNameMap.h"

MultiNameMap::MultiNameMap() {;}

void MultiNameMap::insert(const Uid uid,
                        const MultiName &name)
{
    mUidNameMap.insert(uid, name);
    mNameUidMap.insert(name, uid);
}

void MultiNameMap::remove(const Uid uid)
{
    mNameUidMap.remove(name(uid));
    mUidNameMap.remove(uid);
}

void MultiNameMap::remove(const MultiName &name)
{
    mUidNameMap.remove(uid(name));
    mNameUidMap.remove(name);
}

bool MultiNameMap::contains(const Uid uid) const
{
    return mUidNameMap.contains(uid);
}

bool MultiNameMap::contains(const MultiName &name) const
{
    return mNameUidMap.contains(name);
}

Uid MultiNameMap::uid(const MultiName &name) const
{
    return mNameUidMap.value(name);
}

MultiName MultiNameMap::name(const Uid uid) const
{
    return mUidNameMap.value(uid);
}

MultiName::List MultiNameMap::names() const
{
    return mNameUidMap.keys();
}

QList<Uid> MultiNameMap::uids() const
{
    return mUidNameMap.keys();
}

