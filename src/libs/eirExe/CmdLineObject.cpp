#include "CmdLineObject.h"

#include<QTimer>

#include <eirBase/Debug.h>

CmdLineObject::CmdLineObject(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    mParser.setOptionsAfterPositionalArgumentsMode(
                QCommandLineParser::ParseAsOptions);
    mParser.setSingleDashWordOptionMode(
                QCommandLineParser::ParseAsCompactedShortOptions);
    QTimer::singleShot(100, this,
                       &CmdLineObject::setupApplicationValues);
    EMIT(constructed());
}

void CmdLineObject::addOption(const MultiName &name,
                              const QCommandLineOption &option)
{
    TRACEQFI << name();
    mOptionMap.insert(Sortable(name), option);
    EMIT(optionSet(name));
}

void CmdLineObject::addPositionalArgument(const MultiName &name,
                                          const bool takeAll)
{
    CmdLineObject::CommandLineArgument arg(name);
    addPositionalArgument(arg, takeAll);
}

void CmdLineObject::addPositionalArgument(
        const CmdLineObject::CommandLineArgument &arg,
        const bool takeAll)
{
    CmdLineObject::CommandLineArgument * cla
            = new CmdLineObject::CommandLineArgument(arg);
    if (takeAll) cla->setTakeAll();
    mArguments.append(cla);
    EMIT(argumentSet(mArguments.size(), cla->name()));
}

void CmdLineObject::addHelpOption()
{
    TRACEFN
    mOptions.setFlag(EnableHelp);
    EMIT(optionSet(helpOptionName));
}

void CmdLineObject::addVersionOption()
{
    TRACEFN
    mOptions.setFlag(EnableVersion);
    EMIT(optionSet(versionOptionName));
}

void CmdLineObject::process()
{
    TRACEFN
}

void CmdLineObject::setupApplicationValues()
{
    TRACEFN
    MUSTDO(OrgName AppName)
    NEEDDO(setupApplicationValues)
    NEEDDO(const MultiName cmAhoValueKey)
}

void CmdLineObject::processAddOptions()
{
    TRACEFN
    if (mOptions.testFlag(EnableHelp))
        mParser.addHelpOption();
    if (mOptions.testFlag(EnableVersion))
        mParser.addVersionOption();
    mParser.addOptions(mOptionMap.values());
    foreach (QCommandLineOption opt, mOptionMap.values())
    {
        EMIT(processingOptionAdded(opt));
    } // D20200505aho braces required by EMIT macro TODO?
}

CmdLineObject::CommandLineArgument::
    CommandLineArgument(const MultiName &name)
    : cmName(name)
    , cmArgument(name()) {;}

CmdLineObject::CommandLineArgument
    ::CommandLineArgument(const MultiName &name,
                          const QString &argument,
                          const QString &description,
                          const QString &syntax)
    : cmName(name)
    , cmArgument(argument)
    , cmDescription(description)
    , cmSyntax(syntax) {;}

MultiName CmdLineObject::CommandLineArgument::name() const
{
    return cmName;
}

void CmdLineObject::CommandLineArgument::setTakeAll(bool yes)
{
    mTakeAll = yes;
}

