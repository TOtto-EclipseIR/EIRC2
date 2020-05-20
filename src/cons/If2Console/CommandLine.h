// file: {EIRC2 repo}./crc/cons/If2Console/CommandLine.j
#pragma once

#include <QObject>
//#include <eirExe/BaseCommandLine.h>
#include "../../src/libs/eirExe/BaseCommandLine.h"

#include <eirBase/MultiName.h>

class CommandLine : public BaseCommandLine
{
    Q_OBJECT
public:
    explicit CommandLine(QObject *parent = nullptr);

public slots:
    void setup() override;

public:
    const MultiName filesDirsArgName=MultiName("Argument/FileDirs");

public:
    const MultiName maxFileDirsOptionName
        = MultiName("Option/MaxFileDirs");

signals:

private:
    int mMaxPendingFileDirs=64;


};

