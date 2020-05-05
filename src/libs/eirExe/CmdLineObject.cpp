#include "CmdLineObject.h"

#include <eirBase/Debug.h>

CmdLineObject::CmdLineObject(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    EMIT(constructed());
}

void CmdLineObject::addOption(const MultiName &name,
                              const QCommandLineOption &option)
{
    TRACEQFI << name();
    mParser.addOption(option);
    mOptionMap.insert(name.sortable(), option);
    EMIT(optionSet(name));
}
