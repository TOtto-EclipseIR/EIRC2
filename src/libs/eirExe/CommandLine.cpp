#include "CommandLine.h"

#include <eirBase/Debug.h>


CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("CommandLine");

}
