// file: {EIRC2 repo}./src/libs/eirType/MultiNameMap.h
#pragma once
#include "eirType.h"


#include <QHash>
#include <QList>
#include <QMap>

#include "MultiName.h"
#include "Uid.h"


class EIRTYPE_EXPORT MultiNameMap
{
public:
    MultiNameMap();
    void insert(const Uid uid, const MultiName &name);
    void remove(const Uid uid);
    void remove(const MultiName &name);
    bool contains(const Uid uid) const;
    bool contains(const MultiName &name) const;
    Uid uid(const MultiName &name) const;
    MultiName name(const Uid uid) const;
    MultiName::List names() const;
    QList<Uid> uids() const;

private:
    QHash<Uid, MultiName> mUidNameMap;
    QMap<MultiName, Uid> mNameUidMap;
};

