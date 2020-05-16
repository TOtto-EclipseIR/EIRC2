// file: {repo: EIRC2}./src/libs/eirBase/VarMap.cpp
#include "VarMap.h"

#include "Debug.h"

VarMap::VarMap(const MultiName &name) : mName(name) {;}


VarMap::VarMap(const MultiName &name, const Var::List &vars)
    : mName(name)
{
    foreach (Var var, vars) insert(var);
}

MultiName VarMap::name() const
{
    return mName;
}

bool VarMap::contains(const MultiName &name) const
{
    return mVarMap.contains(name.sortable());
}

VarMap VarMap::insert(const Var &var)
{
    mVarMap.insert(var.name().sortable(), var);
    return *this;
}

Var VarMap::value(const MultiName &name) const
{
    return mVarMap.value(name.sortable());
}

VarMap VarMap::extract(const MultiName &groupName) const
{
    VarMap extractedMap(groupName);
    int nGroupSegments = groupName.segmentCount();
    foreach (Var var, values())
        if (var.name().startsWith(groupName))
        {
            var.set(var.name().firstSegmentsRemoved(nGroupSegments));
            extractedMap.insert(var);
        }
    return extractedMap;
}

void VarMap::insert(const MultiName &groupName,
                    const VarMap &groupVars)
{
    foreach (Var var, groupVars.values())
    {
        var.prependName(groupName);
        insert(var);
    }
}

void VarMap::insert(const VarMap &other, const bool useMapName)
{
    if (useMapName)
    {
        MultiName mapName = other.name();
        foreach (Var var, other.values())
        {
            Var mapVar = var;
            mapVar.prependName(mapName);
            insert(mapVar);
        }

    }
    else
    {
        foreach (Var var, other.values()) insert(var);
    }
}

Var::List VarMap::values() const
{
    return mVarMap.values();
}

Var &VarMap::at(const MultiName &name)
{
    return mVarMap[name.sortable()];
}

BasicName::List VarMap::firstSegmentKeys() const
{
    BasicName::List resultList;
    foreach (Var var, values())
    {
        BasicName firstSegment = var.name().firstSegment();
        if ( ! resultList.contains(firstSegment))
            resultList.append(firstSegment);
    }
    return resultList;
}

VarMap VarMap::operator <<  (const Var &var)
{
    return insert(var);
}

QStringList VarMap::dumpList() const
{
    QStringList qsl;
    foreach(Var var, values())
        qsl << var.dumpString();
    return qsl;
}

void VarMap::dump() const
{
    mName.dump();
    DUMP << dumpList();
}

