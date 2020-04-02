#include "INDIfaceConsole.h"

#include <QTimer>

#include <eirBase/Debug.h>
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
    CONNECT(this, &Application::initFinished,
            this, &INDIfaceConsole::setupDefaults);
//    mpQtOpenCV = new QtOpenCV(this);
    QTimer::singleShot(100, this, &Application::run);
}

void INDIfaceConsole::setupDefaults()
{
    TRACEFN

    QTimer::singleShot(100, this, &INDIfaceConsole::initOpenCV);
}

void INDIfaceConsole::initOpenCV()
{
    TRACEFN
    mpQtOpenCV = new QtOpenCV(this);
    TSTALLOC(mpQtOpenCV)
}
