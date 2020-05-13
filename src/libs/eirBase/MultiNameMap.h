// file: {EIRC2 repo}./src/libs/eirBase/MultiNameMap.h
#pragma once
#include "eirBase.h"


#include <QHash>
#include <QList>
#include <QMap>

#include "MultiName.h"
#include "Uid.h"


class EIRBASE_EXPORT MultiNameMap
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

