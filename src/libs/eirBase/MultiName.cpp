// file: ./Library/Base/MultiName.cpp
#include "MultiName.h"

#include "Debug.h"

// static
const uint MultiName::scmHashSeed = *((uint *)("MultNameHashSeed"));
QChar MultiName::smDelimiter('/');

/*! \class MultiName
 *  \brief The MultiName class provides a multi-element name.
 *  \sa BasicName
 *  \sa Type Library
 *  \sa PersonName
 *  \note This and the BasicName class provide variable-type
 *      names, not intended for names of people.
 *      See (eventually) the PersonName class in the
 *      Type (TBD?) library for that use.
 *  \since v1.01
 */

/*!
 * \brief MultiName::MultiName() constructs an empty name.
 *
 * \since v1.01
 */
MultiName::MultiName(void) {;}

MultiName::MultiName(const QString & qsNames)
{
    set(qsNames);
}

MultiName::MultiName(char * cNames)
{
    set(QString::fromLocal8Bit(cNames));
}

MultiName::MultiName(const QByteArray &baNames)
{
    set(QString::fromLocal8Bit(baNames));
}

MultiName::MultiName(const BasicName::List & other)
{
    mBasicNames = other;
}

MultiName::MultiName(const MultiName &base, const MultiName &name)
{
    mBasicNames = base.mBasicNames + name.mBasicNames;
}

bool MultiName::isEmpty() const
{
    return mBasicNames.isEmpty();
}

void MultiName::clear()
{
    mBasicNames.clear();
}

void MultiName::set(const QString & qsNames)
{
    clear();
    QString qs = qsNames.simplified();
    qs.replace(' ', smDelimiter);
    QStringList qsl = qs.split(smDelimiter, QString::SkipEmptyParts);
    set(qsl);
}

void MultiName::set(const QStringList & qslNames)
{
    foreach(QString s, qslNames)
        mBasicNames << BasicName(s);
}

BasicName MultiName::first() const
{
    return mBasicNames.first();
}

void MultiName::removeLast()
{
    mBasicNames.removeLast();
}

QStringList MultiName::toStringList() const
{
    QStringList qsl;
    foreach(BasicName bn, mBasicNames)
        qsl << bn.toString();
    return  qsl;
}

QString MultiName::toString() const
{
    return join(getDelimiter());
}

QString MultiName::operator ()(void) const
{
    return toString();
}

QVariant MultiName::toVariant() const
{
    return QVariant(toStringList());
}

QString MultiName::sortable() const
{
    return toString().toLower();
}

uint MultiName::hash() const
{
    return qHash(sortable(), scmHashSeed);
}

bool MultiName::operator == (const MultiName & other) const
{
    return sortable() == other.sortable();
}

bool MultiName::operator < (const MultiName & other) const
{
    return sortable() < other.sortable();
}

void MultiName::dump() const
{
    DUMP << toString();
}

QString MultiName::join(
        const QChar & delimiter=smDelimiter) const // protected
{
    QString qs;
    if ( ! isEmpty())
    {
        const QString sDelim(delimiter);
        BasicName::List copy = mBasicNames;
        qs = copy.takeFirst();
        while ( ! copy.isEmpty())
            qs += sDelim + copy.takeFirst().toString();
    }
    return qs;
}

QChar MultiName::getDelimiter(void) // static
{
    return smDelimiter;
}

void MultiName::setDelimiter(const QChar & value) // static
{
    smDelimiter = value;
}

MultiName::operator QVariant() const
{
    return toVariant();
}

MultiName::operator QString() const
{
    return toString();
}

