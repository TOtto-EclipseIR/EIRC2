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
            this, &INDIfaceConsole::initSettings);
    QTimer::singleShot(100, this, &ApplicationHelper::run);
}

void INDIfaceConsole::initResources()
{

}
