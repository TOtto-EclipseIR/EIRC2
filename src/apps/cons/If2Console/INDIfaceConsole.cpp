#include "INDIfaceConsole.h"

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
    mpQtOpenCV = new QtOpenCV(this);
}

void INDIfaceConsole::setupDefaults()
{

}
