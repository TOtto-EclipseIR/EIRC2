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
    void run();

private slots:

signals:

private:
};

