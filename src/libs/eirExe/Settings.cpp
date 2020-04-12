// file: {repo: EIRC2}./src/libs/eirExe/Settings.cpp
#include "Settings.h"

#include <QTimer>

#include <eirBase/Debug.h>

#include "ApplicationHelper.h"

Settings::Settings(ApplicationHelper *parent)
    : QSettings(parent)
    , mpHelper(parent)
{
    TRACEFN
    setObjectName("Settings");
    //QTimer::singleShot(0, this, &Settings::openTemp);
}

ApplicationHelper * Settings::helper()
{
    return mpHelper;
}

void Settings::openTemp()
{
    TRACEFN

}





#if 0
void Settings::set(const Var &var)
{
//    Var old = current(var.name());
    NEEDDO(set)
    if ( ! (old == var)) emit changed(var);
}

void Settings::set(const VarMap &vars)
{
    foreach (Var var, vars.values()) set(var);
}

void Settings::open(BasicName orgName, BasicName argName)
{

}
#endif
