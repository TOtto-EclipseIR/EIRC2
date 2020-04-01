#include "Application.h"

#include <eirBase/Debug.h>

#include "CommandLine.h"
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
