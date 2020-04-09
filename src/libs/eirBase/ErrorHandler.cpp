#include "ErrorHandler.h"

#include <QCoreApplication>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>

ErrorHandler::ErrorHandler()
    : QObject(qApp->parent())
{
    TRACEFN
    setObjectName("ErrorHandler singleton");
    QTimer::singleShot(10, this, &ErrorHandler::registerCodes);
}

bool ErrorHandler::submit(const ErrorHandler::Item item,
                          const bool fail)
{
    TRACEQFI << item.name()();
    if ( ! fail) return false;
    emit triggered(item);
    emit triggered(item.message(';'));
    emit triggered(item.messages());
    item.debug();
    return true;
}

bool ErrorHandler::submit(const ErrorHandler::Code code, const VarMap &vars, const bool fail)
{
    return submit(Item(code, vars), fail);
}

bool ErrorHandler::submit(const MultiName &name, const VarMap &vars, const bool fail)
{
    return submit(Item(name, vars), fail);
}

ErrorHandler::Item ErrorHandler::test(const bool is, const QString &what, ErrorHandler::Item item)
{
    if (is) return Item();
    if (item.isNull()) item = Item::item("ErrorHandler"
                                         "/Expect/Critical");
    VarMap vars;
    vars << Var("What", what);
    item.setVars(vars);
    submit(item);
    return item;
}

bool ErrorHandler::expect(const bool is,
                          const QString &what,
                          ErrorHandler::Item item)
{
    if (is) return true;
    if (item.isNull()) item = Item::item("ErrorHandler"
                                         "/Expect/Critical");
    VarMap vars;
    vars << Var("What", what);
    item.setVars(vars);
    submit(item);
    return false;
}

bool ErrorHandler::tryFileMode(const QIODevice::OpenMode mode,
                               const QString &fileName,
                               const QString &what,
                               const QDir &dir)
{
    return tryFileMode(mode, QFileInfo(dir, fileName), what);
}

bool ErrorHandler::tryFileMode(const QIODevice::OpenMode mode,
                               QFile *file,
                               const QString & what)
{
    return tryFileMode(mode, QFileInfo(file->fileName()), what);
}

bool ErrorHandler::tryFileMode(const QIODevice::OpenMode mode,
                               const QFileInfo &fileInfo,
                               const QString &what)
{
    Success success(true);
    VarMap vars;
    vars << Var("What", what);
    vars << Var("ModesTested", QString::number(mode)
                .toLocal8Bit().toHex().toUpper());
    vars << Var("FileName", fileInfo.fileName());
    vars << Var("FilePath", fileInfo.path());

    if (QIODevice::ExistingOnly & mode && ! fileInfo.exists())
    {
        success.expect(submit("ErrorHandler/tryFileMode/NotExist",
                              vars << Var("Mode", "Existing")));
    }
    else
    {
        if (QIODevice::ReadOnly & mode && ! fileInfo.isReadable())
            success.expect(submit("ErrorHandler/tryFileMode/NotReadable",
                                  vars << Var("Mode", "Readable")));
        if (QIODevice::WriteOnly & mode && ! fileInfo.isWritable())
            success.expect(submit("ErrorHandler/tryFileMode/NotWriteable",
                                  vars << Var("Mode", "Writable")));
    }
    return success;
}

void ErrorHandler::registerCodes()
{
    TRACEFN
    eirBase::registerErrors();
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

bool ErrorHandler::Item::isNull() const
{
    return ! mCode;
}

void ErrorHandler::Item::setVars(const VarMap &vars)
{
    mVars = vars;
}

MultiName ErrorHandler::Item::name() const
{
    return mName;
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

ErrorHandler::Code ErrorHandler::Item::registerCode(const MultiName &name,
                                      const QtMsgType qmt,
                                      const QString format,
                                      const VarMap &itemVars)
{
    TRACEQFI << name() << qmt << format;
    itemVars.dump();
    Item item;
    item.mCode = name.hash();
    item.mName = name;
    item.mMsgType = qmt;
    item.mFormat = format;
    item.mItemVars = itemVars;
    smCodeHash.insert(item.mCode, item);
    return item.mCode;
}

Var::List ErrorHandler::Item::registerCodes(const VarMap::List maps)
{
    Var::List codeVars;
    foreach (VarMap map, maps)
    {
        codeVars.append(Var(map.name(),
                            registerCode(map.name(),
                                         QtMsgType(map.value("QtMsgType")
                                                   .value().toInt()),
                                         map.value("Format").value().toString(),
                                         map.extract("ItemVars"))));
    }
    return codeVars;
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
    default:                  return true;
    }
}

void ErrorHandler::Item::setFatal(const QtMsgType qmt)
{
    smFatalMsgType = qmt;
}
