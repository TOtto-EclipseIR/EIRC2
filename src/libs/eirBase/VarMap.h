// file: {repo: EIRC2}./src/libs/eirBase/VarMap.h
#pragma once
#include "eirBase.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "MultiName.h"
#include "Var.h"

class EIRBASE_EXPORT VarMap
{
public:
    typedef QList<VarMap> List;
    typedef QStack<VarMap> Stack;
    typedef QMap<QString /*MultiName::sortable()*/, VarMap> Map;

public:
    VarMap(const MultiName &name=MultiName());
    VarMap(const MultiName &name,
           const Var::List & vars);
    MultiName name() const;
    bool contains(const MultiName & name) const;
    VarMap insert(const Var &var);
    void insert(const MultiName &key, const QVariant &vari);
    Var value(const MultiName & name) const;
    VarMap extract(const MultiName & groupName) const;
    void insert(const MultiName &groupName,
                const VarMap &groupVars);
    void insert(const VarMap &other, const bool useMapName=false);
    Var::List values() const;
    Var &at(const MultiName &name);
    BasicName::List firstSegmentKeys() const;
    VarMap operator << (const Var &var);
    QStringList dumpList() const;
    void dump() const;

private:
    MultiName mName;
    Var::Map mVarMap;
};

