// file: {repo: EIRC2}./src/libs/eirBase/Id.h
#pragma once
#include "eirBase.h"

#include <QBitArray>
#include <QList>
#include <QMap>
#include <QStack>
#include <QString>
#include <QUuid>
#include <QVariant>

#include "MultiName.h"
#include "Uid.h"
#include "Var.h"

class EIRBASE_EXPORT Id
{
public:
    Id();
    Id(const quint64 key64,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    Id(const MultiName &name,
       const quint64 key64,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    Id(const MultiName &name,
       const QString &desc=QString(),
       const QVariant &data=QVariant());
    ~Id();
    void set(const QUuid &uuid);
    void set(const quint64 key64);
    void set(const MultiName name);
    void set(const QString desc);
    void set(const QVariant data);
    MultiName name() const;
    bool operator <  (const Id & other);
    bool operator == (const Id & other);
    void remove();
    void insert();

public: // static
    static void remove(const Id &id);
    static void insert(const Id &id);
    static Id newId(const MultiName &name);


private:
    QUuid mUuid;
    quint64 mU64Key;
    MultiName mNameKey;
    QBitArray mFlags;
    QString mDescription;
    QVariant mData;

private: // static
    static QMap<QUuid, Id> smUidIdMap;
    static QMap<quint64, QUuid> smUKeyUidMap;
    static QMap<MultiName, QUuid> smNameUidMap;
};

