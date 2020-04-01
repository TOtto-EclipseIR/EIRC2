#include "INDIfaceConsole.h"

#include <eirBase/Debug.h>



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

}
