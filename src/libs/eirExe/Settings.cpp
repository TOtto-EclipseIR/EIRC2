#include "Settings.h"

#include <eirBase/Debug.h>


Settings::Settings(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("Settings");
    mSource = Defaults;
}

Var Settings::current(const MultiName &name) const
{
    Var var = stacked(name);
    if ( ! var.isNull()) return var;
    var = mLocals.value(name);
    if ( ! var.isNull()) return var;
    var = mOverrides.value(name);
    if ( ! var.isNull()) return var;
    var = mDefaults.value(name);
    if ( ! var.isNull()) return var;
    return Var();
}

Var Settings::stacked(const MultiName &name) const
{
    foreach (VarMap vars, mStack)
        if (vars.contains(name))
            return vars.value(name);
    return Var();
}

void Settings::set(Var var)
{
    Var old = current(var.name());
    switch (mSource)
    {
    case Defaults:
        mDefaults.insert(var);
        emit defaultSet(var);
        break;
    case CommandLine:
        mOverrides.insert(var);
        emit overrideSet(var);
        break;
    case Local:
        mLocals.insert(var);
        emit localSet(var);
        break;
    case Stacked:
        mStack.top().insert(var);
        break;
    default:
        WARNQFI << "Settings:Source is lost" << mSource;
        break;
    }
    if ( ! (old == var)) emit changed(var);
}

void Settings::set(VarMap vars)
{
    foreach (Var var, vars.values()) set(var);
}

void Settings::push(VarMap config)
{
    NEEDDO(); NEEDUSE(config);
}

void Settings::pop()
{
    NEEDDO();
}

void Settings::startCommandLine()
{
    mSource = CommandLine;
}

void Settings::finishCommandLine()
{
    mSource = Local;
}
