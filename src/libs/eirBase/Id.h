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
//    Id(const Uid uid=Uid());
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
//    void set(const Uid uid);
    void set(const  QUuid &uuid);
    void set(const quint64 key64);
    void set(const MultiName name);
    void set(const QString desc);
    void set(const QVariant data);
    MultiName name() const;

private:
//    Uid mUid;
    QUuid mUuid;
    quint64 mU64Key;
    MultiName mNameKey;
    QBitArray mFlags;
    QString mDescription;
    QVariant mData;
};

