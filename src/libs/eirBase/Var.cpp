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

MultiName Var::name() const
{
    return mName;
}

void Var::dump()
{
    DUMP << mName() << mDefault << mCurrent;
}
