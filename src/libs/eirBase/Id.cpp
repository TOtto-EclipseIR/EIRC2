// file: {repo: EIRC2}./src/libs/eirBase/Id.cpp
#include "Id.h"

QMap<QUuid, Id> Id::smUidIdMap;
QMap<quint64, QUuid> Id::smUKeyUidMap;
QMap<MultiName, QUuid> Id::smNameUidMap;

// Id::Id(const Uid uid) : mUid(uid), mU64Key(0) {;}

Id::Id() : mU64Key(0) {;}

Id::Id(const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : mUuid(QUuid::createUuid())
    , mU64Key(key64)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const quint64 key64,
       const QString &desc,
       const QVariant &data)
    : mUuid(QUuid::createUuid())
    , mU64Key(key64)
    , mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

Id::Id(const MultiName &name,
       const QString &desc,
       const QVariant &data)
    : mUuid(QUuid::createUuid())
    , mNameKey(name)
    , mDescription(desc)
    , mData(data) {;}

Id::~Id()
{
    remove();
}

void Id::set(const QUuid &uuid)
{
    mUuid = uuid;
}

void Id::set(const MultiName name)
{
    mNameKey = name;
}

MultiName Id::name() const
{
    return mNameKey;
}

bool Id::operator <(const Id &other)
{
    if (mUuid < other.mUuid) return true;
    if (mU64Key < other.mU64Key) return true;
    if (mNameKey < other.mNameKey) return true;
    return false;
}

bool Id::operator ==(const Id &other)
{
    if (mUuid == other.mUuid) return true;
    if (mU64Key == other.mU64Key) return true;
    if (mNameKey == other.mNameKey) return true;
    return false;
}

void Id::remove()
{
    remove(*this);
}

void Id::insert()
{
    insert(*this);
}

void Id::remove(const Id &id)
{
    smUidIdMap.remove(id.mUuid);
    smUKeyUidMap.remove(id.mU64Key);
    smNameUidMap.remove(id.mNameKey);
}

void Id::insert(const Id &id)
{
    smUidIdMap.insert(id.mUuid, id);
    smUKeyUidMap.insert(id.mU64Key, id.mUuid);
    smNameUidMap.insert(id.mNameKey, id.mUuid);
}
