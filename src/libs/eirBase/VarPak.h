// file: {repo: EIRC2}./src/libs/eirBase/VarPak.h
#pragma once
#include "eirBase.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "Id.h"
#include "MultiName.h"
#include "Var.h"
#include "VarMap.h"


typedef Var::List VarList; // TODO? Make this its own class later

class EIRBASE_EXPORT VarPak
{
public:
    VarPak(const Id id=Id());
    void set(const QByteArray &byteArray);
    void set(const Var::List &varList);
    void insert(const VarMap &varMap);
    void set(const int index, const Var &listItem);
    void append(const Var &listItem);
    void insert(const Var &mapItem);
    void insert(const MultiName &key,
                const QVariant &value);
    Var &at(const MultiName &name);
    Var var(const MultiName &name) const;
    QVariant value(const MultiName &name) const;
    Id id() const;
    Id &id();
    QByteArray bytes() const;
    VarList list() const;
    VarList & list(); // non-const
    VarMap map() const;
    VarMap & map(); // non-const

private:
    Id mId;
    QByteArray mBA;
    Var::List mVarList;
    VarMap mVarMap;
};

