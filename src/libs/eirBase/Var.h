#pragma once
#include "eirBase.h"

#include <QList>
#include <QVariant>

#include "MultiName.h"

class EIRBASE_EXPORT Var
{
public:
    typedef QList<Var> List;

public:
    Var(const MultiName & name=MultiName());
    Var(const MultiName & name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    Var(const char * name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    MultiName name() const;
    void dump();

private:
    MultiName mName;
    QVariant mDefault;
    QVariant mCurrent;
};

