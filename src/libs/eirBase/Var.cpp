#include "Var.h"

#include "Debug.h"

Var::Var(const MultiName &name) : mName(name) {;}

Var::Var(const MultiName &name,
         const QVariant &defValue,
         const QVariant &curValue)
    : mName(name)
    , mDefault(defValue)
    , mCurrent(curValue) {;}

Var::Var(const char *name, const QVariant &defValue, const QVariant &curValue)
    : mName(QString(name))
    , mDefault(defValue)
    , mCurrent(curValue) {;}

bool Var::isNull() const
{
    return mName.isEmpty();
}

MultiName Var::name() const
{
    return mName;
}

QVariant Var::current() const
{
    return mCurrent;
}

QVariant Var::value() const
{
    return mCurrent.isValid() ? mCurrent : mDefault;
}

bool Var::operator ==(const Var &other)
{
    return name() == other.name() && value() == other.value();
}

void Var::dump()
{
    DUMP << mName() << mDefault << mCurrent;
}
