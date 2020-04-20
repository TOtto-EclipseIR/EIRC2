// file: {repo: EIRC2}./src/libs/eirBase/Var.h
#pragma once
#include "eirBase.h"

#include <QList>
#include <QMap>
#include <QVariant>

#include "MultiName.h"

class EIRBASE_EXPORT Var
{
public:
    typedef QList<Var> List;
    typedef QMap<QString /* MultiName.sortable() */, Var> Map;

public:
    Var(const MultiName & name=MultiName());
    Var(const MultiName & name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    Var(const char * name,
        const QVariant &defValue,
        const QVariant &curValue=QVariant());
    bool isNull() const;
    MultiName name() const;
    void set(const MultiName &newName);
    void prependName(const MultiName &groupName);
    QVariant current() const;
    QVariant value() const;
    bool operator == (const Var & other);
    void dump();

private:
    MultiName mName;
    QVariant mDefault;
    QVariant mCurrent;
};