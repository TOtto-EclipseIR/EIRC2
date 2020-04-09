#pragma once

#include <QObject>

#include <eirExe/Console.h>

class QtOpenCV;
class Settings;

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

public slots:
    void run();

private slots:
    void initSettings();
    void setupDefaults();
    void initOpenCV();

signals:
    void initFinished();

private:
    Settings * mpSettings=nullptr;
    QtOpenCV * mpQtOpenCV=nullptr;
};

