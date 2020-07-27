#include "StartupDebug.h"

#include <QIODevice>

StartupDebug::StartupDebug()
{
    mpTextStream = new QTextStream(mMessageBuffer);
    qInstallMessageHandler(myBufferedMessageHandler);
}

void StartupDebug::
