#include "INDIfaceConsole.h"

#include <QImage>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/Settings.h>
#include <eirQtCV/eirQtCV.h>
#include <eirQtCV/QtOpenCV.h>


INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
{
    TRACEFN
    setObjectName("INDIfaceConsole");
}

void INDIfaceConsole::initApplication()
{
    TRACEFN
    writeLine("Welcome to INDIfaceConsole");
    CONNECT(this, &ApplicationHelper::initFinished,
            this, &INDIfaceConsole::initResources);
    CONNECT(this, &INDIfaceConsole::applicationInitd,
            this, &INDIfaceConsole::initResources);
    CONNECT(this, &INDIfaceConsole::resoursesInitd,
            this, &INDIfaceConsole::initTaskLine);
    CONNECT(this, &INDIfaceConsole::taskLineInitd,
            this, &INDIfaceConsole::startTaskLine);
    QTimer::singleShot(100, this, &ApplicationHelper::run);
}

void INDIfaceConsole::initResources()
{
    TRACEFN
    writeLine("INDIfaceConsole initialized");
    NEEDDO(Lots)
    emit resoursesInitd();
}

void INDIfaceConsole::initTaskLine()
{
    TRACEFN
    writeLine("INDIfaceConsole loaded");
    NEEDDO(Lots)
    emit taskLineInitd();
}

void INDIfaceConsole::startTaskLine()
{
    TRACEFN
    writeLine("INDIfaceConsole ready");
    NEEDDO(Lots)
}
