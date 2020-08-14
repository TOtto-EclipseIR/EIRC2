// file: ./libs/eirType/Milliseconds.h
#pragma once
#include "eirType.h"

#include <QtGlobal>
#include <QtCore/QDateTime>

class EIRTYPE_EXPORT Milliseconds
{
public:
    Milliseconds(void);
    Milliseconds(qint64 ems);
    Milliseconds(const QDateTime & dt);
    static Milliseconds current(void);
    static Milliseconds fromIso(const QString & isoDateTime);
    static Milliseconds fromString(const QString & dateTime);
    bool isNull(void) const;
    bool isBaseNull(void) const;
    static bool isUtc(void);
    bool isValid(void) const;
    operator qint64(void) const;
    Milliseconds & operator += (const Milliseconds d);
    Milliseconds & operator -= (const Milliseconds d);
    Milliseconds & operator =  (const Milliseconds other);
    void set(const Milliseconds other);
    void nullify(void);
    static qint64 base(void);
    static Milliseconds null(void);
    Milliseconds delta(Milliseconds ems=current()) const;
    QDateTime toDateTime(void) const;
    QString toString(const QString & format=QString()) const;
    static QString baseString(const QString & format=QString());
    QByteArray toByteArray(void) const;

private:
    qint64 mEpochMsec;;
    static const QDateTime mBaseDateTime;
    static const Milliseconds mBaseMsec;
    static const Milliseconds mZoneMsecDelta;
    static const Milliseconds mNullMsec;
};

