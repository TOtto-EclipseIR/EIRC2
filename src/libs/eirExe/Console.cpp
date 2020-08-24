#include "Console.h"

#include <QFile>

#include <eirXfr/Debug.h>

Console::Console(QObject *parent)
    : ApplicationHelper(parent)
    , cmpCoreApp(QCoreApplication::instance())
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

/* This mechanism is broken; simply use qApp-> for now
QCoreApplication *Console::core()
{
    TRACEQFI << QOBJNAME(cmpCoreApp);
    return cmpCoreApp;
}

QObject *Console::appParent()
{
    TRACEQFI << QOBJNAME(core());
    QObject * parent = nullptr;
    if (core()) parent = core()->parent();
    TODO(others);
    TRACERTV() << QOBJNAME(parent);
    return parent;
}
*/

void Console::putChar(const char c)
{
    if (mpIn->putChar(c))
        emit(charPut(c));
    else
        emit(charNotPut(c));
}

void Console::getChar()
{
    char buf[2];
    if (mpIn->getChar(buf))
        emit charGot(buf[0]);
    else
        emit charNotGot();
}

void Console::readLine()
{
    MUSTDO(it);

}

void Console::write(const QString &qs, const bool andFlush)
{
    mpOut->write(qs.toLocal8Bit());
    if (andFlush) mpOut->flush();
}

void Console::writeLine(const QString &qs,
                        const bool andFlush)
{
    write(qs.toLocal8Bit(), false);
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
