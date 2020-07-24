#pragma once

#include <QObject>
#include <eirExe/Console.h>

class QCommandLineParser;

class FaceConsole : public Console
{
    Q_OBJECT
public:
    explicit FaceConsole(QObject *parent = nullptr);

public slots:
    void initializeApplication();

signals:

private:

};

