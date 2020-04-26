#include "Console.h"

#include <QFile>

#include "../../libs/eirBase/Debug.h"

Console::Console(QObject *parent)
    : ApplicationHelper(parent)
    , mpCoreApp(QCoreApplication::instance())
    , mpIn(new QFile(this))
    , mpOut(new QFile(this))
    , mpErr(new QFile(this))
{
    TRACEFN
    TSTALLOC(mpIn)
    TSTALLOC(mpOut)
    TSTALLOC(mpErr)
    setObjectName("Console");
    EXPECT(mpIn->open(stdin, QIODevice::ReadOnly))
    EXPECT(mpOut->open(stdout, QIODevice::WriteOnly))
            EXPECT(mpErr->open(stderr, QIODevice::WriteOnly))
}

CommandLine *Console::commandLine()
{
    return ApplicationHelper::commandLine();
}

void Console::writeLine(const QString &qs,
                        const bool andFlush)
{
    mpOut->write(qs.toLocal8Bit());
    mpOut->write("\n");
    if (andFlush) mpOut->flush();
}

void Console::writeLines(const QStringList &qsl)
{
    foreach (QString qs, qsl) writeLine(qs, false);
    mpOut->flush();
}

void Console::writeErr(const QString &qs, const bool andFlush)
{
    mpErr->write(qs.toLocal8Bit());
    mpErr->write("\n");
    if (andFlush) mpErr->flush();
}

void Console::writeErrs(const QStringList &qsl)
{
    foreach (QString qs, qsl) writeErr(qs, false);
    mpErr->flush();
}

void Console::commandLineComplete()
{
    TRACEFN
    emit commamdLineScanned();
}
