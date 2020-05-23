// file: {EIRC2 repo}/./src/libs/eirExe/CommandLine.cpp
#include "CommandLine.h"

#include <QCoreApplication>
#include <QDir>
#include <QTimer>

#include <eirBase/Debug.h>

#include "CommandLineClientInterface.h"

CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
    , cmExeArgumentList(QCoreApplication::arguments())
{
    TRACEFN
    setObjectName("CommandLine");
    EMIT(constructed());
}

void CommandLine::set(CommandLineClientInterface *interface)
{
    TRACEFN
            mpInterface = interface;
}

QStringList CommandLine::positionalArgumentList() const
{
    return mPositionalArgumentList;
}

QFileInfoList CommandLine::positionalFileInfoList() const
{
    return mPositionalFileDirInfoList;
}

const QStringList CommandLine::exeArguments() const
{
    return cmExeArgumentList;
}

void CommandLine::process()
{
    TRACEQFI << "ExeArgs:" << cmExeArgumentList;
    QStringList arguments;
    mExeFileInfo = QFileInfo(cmExeArgumentList.first());
    arguments = expandFileArguments(cmExeArgumentList.mid(1), '@');
    TRACE << "Expanded:" << arguments;
    arguments = stripConfiguration(arguments);
    TRACE << "Configuration:";
    mConfiguration.dump();
    TRACE << "Post Configuration:" << arguments;
    arguments = extractDirectiveArguments(arguments);
    TRACE << "Post Extract:" << arguments;
    if (mpInterface) arguments = parseQtOptions(arguments);
    TRACE << "virtual setup() complete";

    TODO(?)
    mPositionalArgumentList = arguments;
    TRACE << "PosArgs:" << mPositionalArgumentList;
    mPositionalFileDirInfoList.clear();
    foreach (QString arg, mPositionalArgumentList)
    {
        QFileInfo qfi(arg);
        mPositionalFileDirInfoList
                << ((qfi.exists()) ? qfi : QFileInfo());
    }
}

QStringList CommandLine::expandFileArguments(const QStringList arguments,
                                             const QChar trigger)
{
    TRACEQFI << arguments;
    QStringList expanded;
    foreach (QString arg, arguments)
    {
        if (arg.startsWith(trigger))
        {
            QFileInfo argFileInfo(arg.mid(1));
            TRACE << "Expanding" << argFileInfo.absoluteFilePath();
            TEXPECT(argFileInfo.exists());
            TEXPECT(argFileInfo.isReadable());
            TEXPECT(argFileInfo.isFile());
            expanded << readTxtFileArguments(argFileInfo);
        }
        else
        {
            expanded << arg;
        }
        TRACE << expanded;
    }
    return expanded;
}

QStringList CommandLine::extractDirectiveArguments(
        const QStringList &currentArgs)
{
    TRACEQFI << currentArgs;
    TODO(it)
    return currentArgs;
}

QStringList CommandLine::parseQtOptions(
        const QStringList &currentArgs)
{
    QCommandLineParser parser;

    mpInterface->setup(&parser);

    NEEDDO(Extract from parser)

            return currentArgs;
}

QStringList CommandLine::stripConfiguration(const QStringList &expandedArgs,
                                            const MultiName &prefix,
                                            const QChar &trigger)
{
    TRACEQFI << expandedArgs << prefix() << trigger;
    QStringList remainingArgs;
    foreach (QString arg, expandedArgs)
        if (arg.startsWith(trigger))
            parseConfigArgument(arg, prefix);
        else
            remainingArgs << arg;
    return remainingArgs;
}


void CommandLine::parseConfigArgument(const QString &arg,
                                      const MultiName &prefix)
{
    QStringList qsl = arg.split('=');
    MultiName key = qsl[0].mid(1);
    key.prependName(prefix);
    mConfiguration.insert(key,
        (qsl.size() > 1) ? QVariant(qsl[1]) : QVariant(true));
}

QStringList CommandLine::readTxtFileArguments(const QFileInfo &argFileInfo)
{
    TRACEQFI << argFileInfo.absoluteFilePath();
    QStringList newArgs;
    QFile file(argFileInfo.absoluteFilePath(), this);
    WEXPECT(file.open(QIODevice::ReadOnly | QIODevice::Text))
    WEXPECT(file.exists() && file.isReadable())
    while ( ! file.atEnd())
    {
        QByteArray fileLine = file.readLine().simplified();
        TRACE << "fileLine: {>" << fileLine << "<}";
        if (fileLine.isEmpty() || fileLine.startsWith('#'))
            continue;
        newArgs << fileLine;
    }
    TRACE << file.fileName() << "newArgs" << newArgs;
    return newArgs;
}

void CommandLine::setFileInfoArgs()
{
    NEEDDO(foreach qfi isValid << qfi ! QFI())
}


#ifdef EIRC2_IF2CONSOLE_TAKETWO23
#else
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
