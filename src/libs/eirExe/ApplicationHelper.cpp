#include "ApplicationHelper.h"

#include <QTimer>

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>
#include <eirBase/Milliseconds.h>

#include "CommandLine.h"
#include "Settings.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
//    , mpCommandLine(new CommandLine(this))
  //  , mpSettings(new Settings(this))
{
    TRACEFN
//    TSTALLOC(mpCommandLine)
  //  TSTALLOC(mpSettings)
    setObjectName("Application");

}

void ApplicationHelper::run()
{
    TRACEFN
    QTimer::singleShot(100, this,
                       &ApplicationHelper::initSettings);
}

void ApplicationHelper::setDefault(Var var)
{
    mpSettings->set(var);
}

void ApplicationHelper::initSettings()
{
    TRACEFN
    mpSettings = new Settings(this);
    TSTALLOC(mpSettings);
    QTimer::singleShot(100, this,
                       &ApplicationHelper::setupDefaults);

}


void ApplicationHelper::setupDefaults()
{
    TSTALLOC(mpSettings)
    setDefault(Var("Options/Shutdown", false));
    setDefault(Var("Options/UpdateMsec", 2000));
    QTimer::singleShot(100, this,
                       &ApplicationHelper::initCommandLine);
}

void ApplicationHelper::initCommandLine()
{
    TRACEFN
    mpCommandLine = new CommandLine(this);
    TSTALLOC(mpCommandLine);
    emit initFinished();
}
