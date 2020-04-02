#include "Application.h"

#include <QTimer>

#include <eirBase/Debug.h>

#include "CommandLine.h"
#include "ErrorHandler.h"
#include "Settings.h"

Application::Application(QObject *parent)
    : QObject(parent)
//    , mpCommandLine(new CommandLine(this))
  //  , mpSettings(new Settings(this))
{
    TRACEFN
//    TSTALLOC(mpCommandLine)
  //  TSTALLOC(mpSettings)
    setObjectName("Application");

}

void Application::run()
{
    TRACEFN
    QTimer::singleShot(100, this, &Application::initErrorHandler);
}

void Application::setDefault(Var var)
{
    mpSettings->set(var);
}

void Application::initErrorHandler()
{
    TRACEFN
    TSTALLOC(errorHandler());
    QTimer::singleShot(100, this, &Application::initSettings);

}

void Application::initSettings()
{
    TRACEFN
    mpSettings = new Settings(this);
    TSTALLOC(mpSettings);
    QTimer::singleShot(100, this, &Application::setupDefaults);

}


void Application::setupDefaults()
{
    TSTALLOC(mpSettings)
    setDefault(Var("Options/Shutdown", false));
    setDefault(Var("Options/UpdateMsec", 2000));
    QTimer::singleShot(100, this, &Application::initCommandLine);
}

void Application::initCommandLine()
{
    TRACEFN
    mpCommandLine = new CommandLine(this);
    TSTALLOC(mpCommandLine);
//    QTimer::singleShot(100, this, &Application::initErrorHandler);
    emit initFinished();
}

ErrorHandler *Application::error()
{
    TSTALLOC(mpErrorHandler);
    return mpErrorHandler;
}
