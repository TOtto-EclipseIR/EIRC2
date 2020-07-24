#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include <eirXfr/Debug.h>

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

    //cmpParser->addOption(QCommandLineOption(QStringList()
                                            //<< "exit" << "batch" << "x"));
}
