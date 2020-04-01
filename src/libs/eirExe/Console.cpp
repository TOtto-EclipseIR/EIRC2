#include "Console.h"

#include <QFile>

#include "../../libs/eirBase/Debug.h"

Console::Console(QObject *parent)
    : Application(parent)
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

void Console::writeLine(const QString &qs)
{
    mpOut->write(qs.toLocal8Bit());
    mpOut->write("\n");
    mpOut->flush();
}

void Console::writeErr(const QString &qs)
{
    mpErr->write(qs.toLocal8Bit());
    mpErr->write("\n");
    mpErr->flush();
}
