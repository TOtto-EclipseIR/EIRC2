// file: ./libs/eirType/Milliseconds.cpp

#include "Milliseconds.h"

const QDateTime Milliseconds::mBaseDateTime(
        QDateTime::currentDateTime());

const Milliseconds Milliseconds::mBaseMsec(mBaseDateTime);

const Milliseconds Milliseconds::mZoneMsecDelta(
        (mBaseDateTime.toUTC().toMSecsSinceEpoch())
        - mBaseDateTime.toMSecsSinceEpoch());

const Milliseconds Milliseconds::mNullMsec(INT64_MIN);

Milliseconds::Milliseconds(void) : mEpochMsec(mNullMsec) {;}

Milliseconds::Milliseconds(qint64 ems) : mEpochMsec(ems) {;}

Milliseconds::Milliseconds(const QDateTime & dt)
    : mEpochMsec(dt.isValid() ? dt.toMSecsSinceEpoch() : INT64_MIN) {;}

Milliseconds Milliseconds::current(void)
{
    return Milliseconds(QDateTime::currentMSecsSinceEpoch());
}

Milliseconds Milliseconds::fromIso(const QString & isoDateTime)
{
    return Milliseconds(QDateTime::fromString(isoDateTime, Qt::ISODate));
}

Milliseconds Milliseconds::fromString(const QString & dateTime)
{
    qint64 i64 = dateTime.toLongLong();
    return Milliseconds((i64 > 3000)
                           ? QDateTime::fromMSecsSinceEpoch(i64)
                           : QDateTime::fromString(dateTime, Qt::ISODate));
}

bool Milliseconds::isValid(void) const
{
    return toDateTime().isValid();
}

bool Milliseconds::isNull(void) const
{
    return mNullMsec == mEpochMsec;
}

bool Milliseconds::isBaseNull(void) const
{
    return mNullMsec == mBaseMsec;
}

bool Milliseconds::isUtc(void)
{
    return 0 == mZoneMsecDelta;
}

Milliseconds::operator qint64(void) const
{
    return mEpochMsec;;
}

Milliseconds & Milliseconds::operator += (const Milliseconds d)
{
    mEpochMsec += d;
    return *this;
}

Milliseconds & Milliseconds::operator -= (const Milliseconds d)
{
    mEpochMsec -= d;
    return *this;
}

Milliseconds & Milliseconds::operator = (const Milliseconds other)
{
    mEpochMsec = other.mEpochMsec;
    return *this;
}

void Milliseconds::set(const Milliseconds other)
{
    mEpochMsec = other.mEpochMsec;
}

void Milliseconds::nullify(void)
{
    mEpochMsec = mNullMsec;
}

qint64 Milliseconds::base(void)
{
    return mBaseMsec;
}

Milliseconds Milliseconds::null(void)
{
    return mNullMsec;
}

Milliseconds Milliseconds::delta(Milliseconds ems) const
{
    return Milliseconds(ems - mEpochMsec);
}

QDateTime Milliseconds::toDateTime(void) const
{
    return QDateTime::fromMSecsSinceEpoch(mEpochMsec);
}

QString Milliseconds::toString(const QString & format) const
{
    return toDateTime().toString(format.isEmpty()
                                 ? "yyyy/MM/dd hh:mm:ss.zzz"
                                 : format);
}

QString Milliseconds::baseString(const QString & format)
{
    return QDateTime::fromMSecsSinceEpoch(mBaseMsec).toString(format);
}

QByteArray Milliseconds::toByteArray() const
{
    return QByteArray((char *)(&mEpochMsec), sizeof (mEpochMsec));
}
