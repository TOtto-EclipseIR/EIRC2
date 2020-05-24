#include "ConfigObject.h"

#include <eirBase/Debug.h>

ConfigObject::ConfigObject(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("ConfigObject");
    TODO(All)
}

Configuration ConfigObject::configuration() const
{
    return mConfiguration;
}

Configuration ConfigObject::configuration(const MultiName &groupName) const
{
    return mConfiguration.extract(groupName);
}

void ConfigObject::set(VarMap varMap)
{
    TRACEFN
    mConfiguration.insert(varMap);
    mConfiguration.dump();
}

void ConfigObject::set(VarMap varMap, MultiName groupName)
{
    TRACEFN
    mConfiguration.insert(groupName, varMap);
    mConfiguration.dump();
}

void ConfigObject::set(Var var)
{
    TRACEFN
    NEEDUSE(var);
    NEEDDO(it)
}

void ConfigObject::setDefault(Var var)
{
    TRACEFN
    NEEDUSE(var); NEEDDO(it)
}

void ConfigObject::setDefault(MultiName key, QVariant defaultVari)
{
    TRACEFN
    NEEDUSE(key); NEEDUSE(defaultVari); NEEDDO(it)
}

void ConfigObject::setCurrent(Var var)
{
    TRACEFN
    NEEDUSE(var); NEEDDO(it)
}

void ConfigObject::setCurrent(MultiName key, QVariant currentVari)
{
    TRACEFN
    NEEDDO(it)
    NEEDUSE(key); NEEDUSE(currentVari); NEEDDO(it)
}


