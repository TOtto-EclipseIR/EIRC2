// file: {EIRC2 repo}/./src/libs/eirExe/CommandLineMachine.h
#pragma once
#include "eirExe.h"


#include <QStateMachine>

#include <QObject>
#include <QState>

class BaseCommandLine;

class EIREXE_EXPORT CommandLineMachine : public QStateMachine
{
    Q_OBJECT
public:
    explicit CommandLineMachine(BaseCommandLine *commandLine = nullptr);
    BaseCommandLine * commandLine() const;

protected slots:
    void setup();
    void initialize();

signals:

private:
    BaseCommandLine * const cmpCommandLine=nullptr;

    QState * mpStartState=nullptr;
    QState * mpInitialState=nullptr;
    QStateMachine * mpParsingSuperState=nullptr;
    QState * mpQtParsingState=nullptr;
    QState * mpIncludeParsingState=nullptr;
    QState * mpConfigParsingState=nullptr;
    QState * mpSettingsParsingState=nullptr;
    QState * mpArgParsingState=nullptr;
    QState * mpResultsState=nullptr;

};

