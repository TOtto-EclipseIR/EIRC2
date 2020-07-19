#include "FaceConsole.h"

#include <QDateTime>

#include <eirBase/Debug.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
{
    TRACEFN;
    setObjectName("FaceConsole");
    QTimer::singleShot(100, this, &FaceConsole::initializeApplication);
    TRACERTV();
}

void FaceConsole::initializeApplication()
{
    TRACEFN;

    QLocale locale;
    writeLine(QString("%1 %2 started %3").arg(qApp->applicationName()).arg(qApp->applicationVersion()).arg(locale.toString(QDateTime::currentDateTime())));
}