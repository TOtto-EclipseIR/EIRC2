// file: {EIRC2 repo}/./src/libs/eirExe/CommandLine.cpp
#include "CommandLine.h"

#include <QCoreApplication>
#include <QTimer>

#include <eirBase/Debug.h>

//#include "CommandLineMachine.h"

CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
    , cmExeArgumentList(QCoreApplication::arguments())
{
#ifdef EIRC2_IF2CONSOLE_TAKETWO23
    TRACEFN
#else
    mParser.setOptionsAfterPositionalArgumentsMode(
                QCommandLineParser::ParseAsOptions);
    mParser.setSingleDashWordOptionMode(
                QCommandLineParser::ParseAsCompactedShortOptions);
    QTimer::singleShot(100, this, &CommandLine::setupApplicationValues);
    EMIT(constructed());
#endif
    QTimer::singleShot(100, this, &CommandLine::processFourthPass);
}

#ifdef EIRC2_IF2CONSOLE_TAKETWO23
const QStringList CommandLine::exeArguments() const
{
    return cmExeArgumentList;
}

void CommandLine::processFourthPass()
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

void CommandLine::processFifthPass()
{
    TRACEFN
    NEEDDO(it);
    foreach (QString arg, mFifthPassArguments)
        if (arg.startsWith('/'))
            parseConfigArgument(arg);
        else
            mSixthPassArguments.append(arg);
}

void CommandLine::processSixthPass()
{
    TRACEFN
    NEEDDO(it);
    foreach (QString arg, mFifthPassArguments)
    {
        mPositionalFileDirInfoList << QFileInfo(arg);
    }
}

void CommandLine::parseConfigArgument(const QString &arg)
{
    QStringList qsl = arg.split('=');
    MultiName key = qsl[0].mid(1);
    if (qsl.size() > 1)
        mConfiguration.insert(key, QVariant(qsl[1]));
    else
        mConfiguration.insert(key, QVariant(true));

}

QStringList CommandLine::readTxtFileArguments(const QString &arg)
{
    QStringList newArgs;
    QFile file(arg, this);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray qba = file.readAll();
    QString args = qba;
    newArgs = args.simplified().split(' ');
    return newArgs;
}

#else
QFileInfoList CommandLine::positionalFileInfoList() const
{
    return mPositionalFileDirInfoList;
}

Configuration CommandLine::configuration() const
{
    return mConfiguration;
}

void CommandLine::addOption(const QCommandLineOption &option)
{
    TRACEQFI << option.names();
    mParser.addOption(option);
    EMIT(optionSet(option.names().first()));
}

void CommandLine::addPositionalArgument(const MultiName &name,
                                            const QString &desc,
                                            const QString &syntax)
{
    TRACEQFI << name();
    mParser.addPositionalArgument(name(), desc, syntax);
}

void CommandLine::noHelpOption()
{
    TRACEFN
    mOptions.setFlag(DisableHelp);
    EMIT(optionSet(helpOptionName));
}

void CommandLine::noVersionOption()
{
    TRACEFN
    mOptions.setFlag(DisableVersion);
    EMIT(optionSet(versionOptionName));
}

CommandLine::Options &CommandLine::rwrefOptions()
{
    TRACEFN
    WARN << "Writable";
    return mOptions;
}

void CommandLine::setupApplicationValues()
{
    TRACEFN
    NEEDDO(OrgName AppName)
    NEEDDO(setupApplicationValues)
    NEEDDO(const MultiName cmAhoValueKey)
}

void CommandLine::setupSettings()
{
    TRACEFN
    NEEDDO(setupSettings);
}

void CommandLine::setupArguments()
{
    TRACEFN
    NEEDDO(setupArguments);
}


void CommandLine::process()
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


void CommandLine::processSecondPass()
{
    TRACEFN
    mParser.process(cmExeArgumentList);
    mThirdPassArguments = mParser.positionalArguments();
}

void CommandLine::processThirdPass()
{
    TRACEFN
    NEEDDO(it);
}


void CommandLine::handleAmpersandArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void CommandLine::handleBangArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void CommandLine::handlePercentArgument(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
}

void CommandLine::handlePositionalArguments()
{
    TRACEFN
    NEEDDO(it);
}

void CommandLine::handlePositionalFileDir(const QString &arg)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(arg)
    TODO(If QFI.exists() append QfI else null QFI())
}
#endif
