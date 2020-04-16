// file: {repo:EIRC2}./src/libs/eirType/Uid.h
#pragma once
#include "eirBase.h"

#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>
#include <QUuid>

#include "UInt128.h"

class EIRBASE_EXPORT Uid : public QUuid
{
public:
    QList<Uid> List;

public:

public:
    Uid(void);
    Uid(const QUuid quuid);
    Uid(const UInt128 u128);
    Uid(const QString & sUid,
        const QUuid::StringFormat fmt,
        const QUuid::Version ver=QUuid::Time,
        const QUuid::Variant var=QUuid::DCE);
    Uid(const QByteArray & rawUid,
        const QUuid::Version ver=QUuid::Time,
        const QUuid::Variant var=QUuid::DCE);

    Uid set(const UInt128 u128);
    Uid set(const QString & sUid,
            const QUuid::StringFormat fmt,
            const QUuid::Version ver=QUuid::Time,
            const QUuid::Variant var=QUuid::DCE);
    Uid set(const QByteArray & rawUid,
            const QUuid::Version ver=QUuid::Time,
            const QUuid::Variant var=QUuid::DCE);
    QByteArray toByteArray(void) const;
    UInt128 toU128(void) const;

public: // static
    static Uid create();

private:
};

