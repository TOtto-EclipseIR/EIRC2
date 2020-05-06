#include "BaseCommandLine.h"

#include <QCoreApplication>
#include <QTimer>

#include <eirBase/Debug.h>

BaseCommandLine::BaseCommandLine(QObject *parent)
    : QObject(parent)
    , cmExeArgumentList(QCoreApplication::arguments())
{
    TRACEFN
    mParser.setOptionsAfterPositionalArgumentsMode(
                QCommandLineParser::ParseAsOptions);
    mParser.setSingleDashWordOptionMode(
                QCommandLineParser::ParseAsCompactedShortOptions);
    QTimer::singleShot(100, this,
                       &BaseCommandLine::setupApplicationValues);
    EMIT(constructed());
}

QFileInfoList BaseCommandLine::positionalFileInfoList() const
{
    return mPositionalFileDirInfoList;
}

void BaseCommandLine::addOption(const MultiName &name,
                              const QCommandLineOption &option)
{
    TRACEQFI << name();
    mOptionMap.insert(Sortable(name), option);
    EMIT(optionSet(name));
}

void BaseCommandLine::addPositionalArgument(const MultiName &name,
                                          const bool takeAll)
{
    BaseCommandLine::CommandLineArgument arg(name);
    addPositionalArgument(arg, takeAll);
}

void BaseCommandLine::addPositionalArgument(
        const BaseCommandLine::CommandLineArgument &arg,
        const bool takeAll)
{
    BaseCommandLine::CommandLineArgument * cla
            = new BaseCommandLine::CommandLineArgument(arg);
    if (takeAll) cla->setTakeAll();
    mArguments.append(cla);
    EMIT(argumentSet(mArguments.size(), cla->name()));
}

void BaseCommandLine::addHelpOption()
{
    TRACEFN
    mOptions.setFlag(EnableHelp);
    EMIT(optionSet(helpOptionName));
}

void BaseCommandLine::addVersionOption()
{
    TRACEFN
    mOptions.setFlag(EnableVersion);
    EMIT(optionSet(versionOptionName));
}

BaseCommandLine::Options &BaseCommandLine::rwrefOptions()
{
    return mOptions;
}

void BaseCommandLine::setupApplicationValues()
{
    TRACEFN
    MUSTDO(OrgName AppName)
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
    processAddOptions();
    processAddArguments();
    processSecondPass();
    processThirdPass();
    processFourthPass();
    EMIT(processingFinished());
}

void BaseCommandLine::processAddOptions()
{
    TRACEFN
    if (rwrefOptions().testFlag(EnableHelp))
        mParser.addHelpOption();
    if (rwrefOptions().testFlag(EnableVersion))
        mParser.addVersionOption();
    mParser.addOptions(mOptionMap.values());
    foreach (QCommandLineOption opt, mOptionMap.values())
    {
        EMIT(processingOptionAdded(opt));
    } // D20200505aho braces required by EMIT macro TODO?
}

void BaseCommandLine::processAddArguments()
{
    TRACEFN
    foreach (CommandLineArgument * arg, mArguments)
    {
        TRACE << arg->name()();
        mParser.addPositionalArgument(arg->argument(),
            arg->description(), arg->syntax());
    }
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

BaseCommandLine::CommandLineArgument::
    CommandLineArgument(const MultiName &name)
    : cmName(name)
    , cmArgument(name()) {;}

BaseCommandLine::CommandLineArgument
    ::CommandLineArgument(const MultiName &name,
                          const QString &argument,
                          const QString &description,
                          const QString &syntax)
    : cmName(name)
    , cmArgument(argument)
    , cmDescription(description)
    , cmSyntax(syntax) {;}

MultiName BaseCommandLine::CommandLineArgument::name() const
{
    return cmName;
}

QString BaseCommandLine::CommandLineArgument::argument() const
{

}

QString BaseCommandLine::CommandLineArgument::description() const
{

}

QString BaseCommandLine::CommandLineArgument::syntax() const
{

}

void BaseCommandLine::CommandLineArgument::setTakeAll(bool yes)
{
    mTakeAll = yes;
}

