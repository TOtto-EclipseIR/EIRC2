// file: {EIRC2 repo}/./src/libs/eirExe/CommandLineMachine.cpp
#include "CommandLineMachine.h"

#include <QTimer>

#include <eirBase/Debug.h>

CommandLineMachine::CommandLineMachine(BaseCommandLine *cmdLine)
    : QStateMachine(nullptr)
    , cmpCommandLine(cmdLine)
    , mpStartState(this)
    , mpInitialState(this)
    , mpParsingSuperState(this)
    , mpQtParsingState(this)
    , mpIncludeParsingState(this)
    , mpConfigParsingState(this)
    , mpSettingsParsingState(this)
    , mpArgParsingState(this)
    , mpResultsState(this)
{
    TRACEFN
    TSTALLOC(cmdLine)
    setObjectName("CommandLineMachine");
    setParent((QObject *)(cmdLine));

    TSTALLOC(mpStartState)
    TSTALLOC(mpInitialState)
    TSTALLOC(mpParsingSuperState)
    TSTALLOC(mpQtParsingState)
    TSTALLOC(mpQtParsingState)
    TSTALLOC(mpIncludeParsingState)
    TSTALLOC(mpSettingsParsingState)
    TSTALLOC(mpArgParsingState)
    TSTALLOC(mpResultsState)

    QTimer::singleShot(100, this, &CommandLineMachine::setup);
}

BaseCommandLine *CommandLineMachine::commandLine() const
{
    return cmpCommandLine;
}

void CommandLineMachine::setup()
{
    TRACEFN
    TSTALLOC(mpStartState)
    TSTALLOC(mpInitialState)
    setInitialState(mpStartState);
    addState(mpInitialState);

    addTransition(this, &CommandLineMachine::initialize, mpInitialState);

    NEEDDO(Lots)
    QStateMachine::start();
}

void CommandLineMachine::initialize()
{
    TRACEFN
}
