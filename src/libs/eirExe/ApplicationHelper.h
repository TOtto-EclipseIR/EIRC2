#pragma once
#include "eirExe.h"

#include <QObject>

#include <eirBase/Var.h>
class CommandLine;
class ErrorHandler;
class Settings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);

public slots:
    void run();
    void setDefault(Var var);

private slots:
    void initSettings();
    void setupDefaults();
    void initCommandLine();

public: // static

signals:
    void initFinished();

private:
    CommandLine * mpCommandLine=nullptr;
    Settings * mpSettings=nullptr;

};

