// file: {repo: EIRC2}./src/libs/eirBase/Id.cpp
#include "Id.h"

// Id::Id(const Uid uid) : mUid(uid), mU64Key(0) {;}

Id::Id() : mU64Key(0) {;}

Id::Id(const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : /* mUid(Uid::create())
    , */ mU64Key(key64)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : /* mUid(Uid::create())
    , */ mU64Key(key64)
    , mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const QString &desc,
       const QVariant &data)
    : /* mUid(Uid::create())
    , */ mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

MultiName Id::name() const
{
    return mNameKey;
}
