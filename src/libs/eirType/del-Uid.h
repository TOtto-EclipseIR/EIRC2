// file: {repo:EIRC2}./src/libs/eirType/Uid.h
#pragma once
#include "eirType.h"

#include <QByteArray>
#include <QPair>
#include <QString>
#include <QUuid>

class EIRTYPE_EXPORT Uid : public QUuid
{
public:
    class UInt128
    {
    public:
        typedef QPair<quint64, quint64> Pair128;
    private:
    public:
        UInt128(void);
        UInt128(const Pair128 upperLowerPair);
        UInt128(const quint64 upper, const quint64 lower);
        UInt128(const QByteArray & byteArray);
        UInt128(const quint8 bytes[8]);
        UInt128(const QUuid quid);
        UInt128 set(const Pair128 upperLowerPair);
        UInt128 set(const quint64 upper, const quint64 lower);
        UInt128 set(const QByteArray & byteArray);
        UInt128 set(const quint8 bytes[8]);
        UInt128 set(const QUuid quid);
        UInt128 toU128(void) const;
        QString toHex(void) const;
        QByteArray toByteArray(void)  const;
        bool isNull(void) const;
        void nullify(void);
        quint64 upper() const;
        quint64 lower() const;
        bool operator == (const UInt128 & other);
    private:
        union
        {
            Pair128 mUpperLowerPair;
            quint8 mBytes[8];
        };
    };

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

