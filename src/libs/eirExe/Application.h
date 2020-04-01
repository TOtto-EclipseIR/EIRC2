#pragma once
#include "eirExe.h"

#include <QObject>

class CommandLine;
class Settings;

class EIREXE_EXPORT Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);

public slots:
    void run();

signals:

private:
    CommandLine * mpCommandLine=nullptr;
    Settings * mpSettings=nullptr;

};

