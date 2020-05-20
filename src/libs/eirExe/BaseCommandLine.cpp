// file: {EIRC2 repo}/./src/libs/eirExe/BaseCommandLine.cpp
#include "BaseCommandLine.h"

#include <QCoreApplication>
#include <QTimer>

#include <eirBase/Debug.h>

#include "CommandLineMachine.h"

BaseCommandLine::BaseCommandLine(QObject *parent)
    : QObject(parent)
    , cmpMachine(new CommandLineMachine(this))
    , cmExeArgumentList(QCoreApplication::arguments())
{
    TRACEFN
    mParser.setOptionsAfterPositionalArgumentsMode(
                QCommandLineParser::ParseAsOptions);
    mParser.setSingleDashWordOptionMode(
                QCommandLineParser::ParseAsCompactedShortOptions);
//    QTimer::singleShot(100, this, &BaseCommandLine::setupApplicationValues);
    QTimer::singleShot(100, this, &BaseCommandLine::processFourthPass);
    EMIT(constructed());
}

CommandLineMachine *BaseCommandLine::machine() const
{
    return cmpMachine;
}

QFileInfoList BaseCommandLine::positionalFileInfoList() const
{
    return mPositionalFileDirInfoList;
}

const QStringList BaseCommandLine::exeArguments() const
{
    return cmExeArgumentList;
}

Configuration BaseCommandLine::configuration() const
{
    return mConfiguration;
}

void BaseCommandLine::parseConfigArgument(const QString &arg)
{
    QStringList qsl = arg.split('=');
    MultiName key = qsl[0].mid(1);
    if (qsl.size() > 1)
        mConfiguration.insert(key, QVariant(qsl[1]));
    else
        mConfiguration.insert(key, QVariant(true));

}

QStringList BaseCommandLine::readTxtFileArguments(const QString &arg)
{
    QStringList newArgs;
    QFile file(arg, this);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray qba = file.readAll();
    QString args = qba;
    newArgs = args.simplified().split(' ');
    return newArgs;
}

void BaseCommandLine::addOption(const QCommandLineOption &option)
{
    TRACEQFI << option.names();
    mParser.addOption(option);
    EMIT(optionSet(option.names().first()));
}

void BaseCommandLine::addPositionalArgument(const MultiName &name,
                                            const QString &desc,
                                            const QString &syntax)
{
    TRACEQFI << name();
    mParser.addPositionalArgument(name(), desc, syntax);
}

void BaseCommandLine::noHelpOption()
{
    TRACEFN
    mOptions.setFlag(DisableHelp);
    EMIT(optionSet(helpOptionName));
}

void BaseCommandLine::noVersionOption()
{
    TRACEFN
    mOptions.setFlag(DisableVersion);
    EMIT(optionSet(versionOptionName));
}

BaseCommandLine::Options &BaseCommandLine::rwrefOptions()
{
    TRACEFN
    WARN << "Writable";
    return mOptions;
}

void BaseCommandLine::setupApplicationValues()
{
    TRACEFN
    NEEDDO(OrgName AppName)
    NEEDDO(setupApplicationValues)
    NEEDDO(const MultiName cmAhoValueKey)
}

void BaseCommandLine::setupSettings()
{
    TRACEFN
    NEEDDO(setupSettings);
}

void BaseCommandLine::setupArguments()
{
    TRACEFN
    NEEDDO(setupArguments);
}


void BaseCommandLine::process()
{
    TRACEFN
    EMIT(processingStarted());
    setupApplicationValues();
    setupSettings();
    setup();
    processSecondPass();
    processThirdPass();
    processFourthPass();
    EMIT(processingFinished());
}


void BaseCommandLine::processSecondPass()
{
    TRACEFN
    mParser.process(cmExeArgumentList);
    mThirdPassArguments = mParser.positionalArguments();
}

void BaseCommandLine::processThirdPass()
{
    TRACEFN
    NEEDDO(it);
}

void BaseCommandLine::processFourthPass()
{
    TRACEFN
    NEEDDO(it);
    foreach (QString arg, cmExeArgumentList)
    {
        if (arg.startsWith('@'))
            foreach (QString fileArg, readTxtFileArguments(arg))
                mFifthPassArguments.prepend(fileArg);
        else
            mFifthPassArguments.append(arg);
    }
}

void BaseCommandLine::processFifthPass()
{
    TRACEFN
    NEEDDO(it);
    foreach (QString arg, mFifthPassArguments)
        if (arg.startsWith('/'))
            parseConfigArgument(arg);
        else
            mSixthPassArguments.append(arg);
}

void BaseCommandLine::processSixthPass()
{
    TRACEFN
    NEEDDO(it);
    foreach (QString arg, mFifthPassArguments)
    {
        mPositionalFileDirInfoList << QFileInfo(arg);
    }
}

void BaseCommandLine::handleAmpersandArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void BaseCommandLine::handleBangArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void BaseCommandLine::handlePercentArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void BaseCommandLine::handlePositionalArguments()
{
    TRACEFN
    NEEDDO(it);
}

void BaseCommandLine::handlePositionalFileDir(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
    TODO(If QFI.exists() append QfI else null QFI())
}
