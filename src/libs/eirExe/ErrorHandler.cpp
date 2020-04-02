#include "ErrorHandler.h"

#include <QCoreApplication>

#include <eirBase/Debug.h>


ErrorHandler::ErrorHandler()
    : QObject(qApp->parent())
{
    TRACEFN
    setObjectName("ErrorHandler singleton");
}

QHash<ErrorHandler::Code, ErrorHandler::Item> ErrorHandler::Item::smCodeHash;
QtMsgType ErrorHandler::Item::smFatalMsgType = QtCriticalMsg;

ErrorHandler::Item::Item() {;}

ErrorHandler::Item::Item(const uint hash, const VarMap &vars)
    : mMsec(Milliseconds::current())
{
    if (isValid(hash)) *this = item(hash);
    mVars = vars;
}

ErrorHandler::Item::Item(const MultiName &name, const VarMap &vars)
    : mMsec(Milliseconds::current())
{
    if (isValid(name)) *this = item(name);
    mVars = vars;
}

QStringList ErrorHandler::Item::messages() const
{
    QStringList msgs;
    msgs << QString("%1 %2 [0x%3]")
            .arg(mMsec.toString("hh:MM:ss.zzz"))
            .arg(mName.toString()).arg(mCode, 0, 16, QChar('0'));
    foreach (Var var, mVars.values())
    {
        msgs << QString("%1: %2 [%3]").arg(var.name()())
                .arg(var.value().toString())
                .arg(mItemVars.value(var.name()).value().toString());
    }
    return msgs;
}

QString ErrorHandler::Item::message(const QChar sep) const
{
    return messages().join(sep);
}

bool ErrorHandler::Item::debug() const
{
    bool fatal = isFatal();
    switch (mMsgType)
    {
    case QtDebugMsg:    TRACE   << message(';');       break;
    case QtInfoMsg:     INFO    << message(';');       break;
    case QtWarningMsg:  WARN    << message(';');       break;
    case QtCriticalMsg: ERROR   << message(';');       break;
    case QtFatalMsg:    ERROR   << message(';');       break;
    }
    if (fatal)  ABORT("Fatal Error");
    return fatal;
}

uint ErrorHandler::Item::registerCode(const MultiName &name,
                                      const QtMsgType qmt,
                                      const QString format,
                                      const VarMap &itemVars)
{
    Item item;
    item.mCode = name.hash();
    item.mName = name;
    item.mMsgType = qmt;
    item.mFormat = format;
    item.mItemVars = itemVars;
    smCodeHash.insert(item.mCode, item);
    return item.mCode;
}

bool ErrorHandler::Item::isValid(const MultiName &name)
{
    return  !! registeredCode(name);
}

bool ErrorHandler::Item::isValid(const ErrorHandler::Code code)
{
    return  smCodeHash.contains(code);
}

ErrorHandler::Code ErrorHandler::Item::registeredCode(
        const MultiName &name)
{
    Code code = name.hash() ;
    return (isValid(code)) ? code : 0;
}

ErrorHandler::Item ErrorHandler::Item::item(const MultiName &name)
{
    return isValid(name) ? smCodeHash.value(name.hash()) : ErrorHandler::Item();
}

ErrorHandler::Item ErrorHandler::Item::item(const ErrorHandler::Code code)
{
    return isValid(code) ? smCodeHash.value(code) : ErrorHandler::Item();
}

bool ErrorHandler::Item::isFatal() const
{
    switch (mMsgType)
    {
    case QtDebugMsg:    /*0*/ return false;
    case QtInfoMsg:     /*4*/ return false;
    case QtWarningMsg:  /*1*/ return smFatalMsgType >= QtWarningMsg;
    case QtCriticalMsg: /*2*/ return smFatalMsgType >= QtCriticalMsg;
    case QtFatalMsg:    /*3*/ return smFatalMsgType >= QtFatalMsg;
    }
}

void ErrorHandler::Item::setFatal(const QtMsgType qmt)
{
    smFatalMsgType = qmt;
}
