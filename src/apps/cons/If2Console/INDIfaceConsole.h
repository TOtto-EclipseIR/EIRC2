#pragma once

#include <QObject>

#include <eirExe/Console.h>
#include <eirQtCV/QtOpenCV.h>

class Settings;

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

public slots:
    void initApplication();

private slots:
    void initResources();
    void initTaskLine();
    void startTaskLine();

signals:
    void applicationInitd();
    void resoursesInitd();
    void taskLineInitd();
    void taskLineStarted();

private:
};

