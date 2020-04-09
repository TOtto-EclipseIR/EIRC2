#include "INDIfaceConsole.h"

#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/Settings.h>
#include <eirQtCV/QtOpenCV.h>


INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
{
    TRACEFN
    setObjectName("INDIfaceConsole");
}

void INDIfaceConsole::run()
{
    TRACEFN
    writeLine("Welcome to INDIfaceConsole");
    CONNECT(this, &ApplicationHelper::initFinished,
            this, &INDIfaceConsole::initSettings);
    QTimer::singleShot(100, this,
                       &ApplicationHelper::run);
}

void INDIfaceConsole::initSettings()
{
    TRACEFN

    QTimer::singleShot(100, this,
                       &INDIfaceConsole::setupDefaults);

}

void INDIfaceConsole::setupDefaults()
{
    TRACEFN

    QTimer::singleShot(100, this,
                       &INDIfaceConsole::initOpenCV);
}

void INDIfaceConsole::initOpenCV()
{
    TRACEFN
    mpQtOpenCV = new QtOpenCV(this);
    TSTALLOC(mpQtOpenCV)
    emit initFinished();
}
