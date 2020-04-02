#pragma once
#include "eirExe.h"

#include <QObject>

#include <eirBase/Var.h>
class CommandLine;
class ErrorHandler;
class Settings;

class EIREXE_EXPORT Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);
    ErrorHandler * error();

public slots:
    void run();
    void setupDefaults();
    void setDefault(Var var);

public: // static

signals:

private:
    ErrorHandler * mpErrorHandler=nullptr;
    CommandLine * mpCommandLine=nullptr;
    Settings * mpSettings=nullptr;

};

