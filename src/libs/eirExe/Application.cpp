#include "Application.h"

#include <eirBase/Debug.h>

#include "CommandLine.h"
#include "ErrorHandler.h"
#include "Settings.h"

Application::Application(QObject *parent)
    : QObject(parent)
    , mpCommandLine(new CommandLine(this))
    , mpSettings(new Settings(this))
{
    TRACEFN
    TSTALLOC(mpCommandLine)
    TSTALLOC(mpSettings)
    setObjectName("Application");

}

void Application::run()
{
    TRACEFN

}

void Application::setupDefaults()
{
    TSTALLOC(mpSettings)
    setDefault(Var("Options/Shutdown", false));
    setDefault(Var("Options/UpdateMsec", 2000));
}

void Application::setDefault(Var var)
{
    mpSettings->set(var);
}

ErrorHandler *Application::error()
{
    TSTALLOC(mpErrorHandler);
    return mpErrorHandler;
}
