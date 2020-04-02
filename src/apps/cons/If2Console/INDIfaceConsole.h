#pragma once

#include <QObject>
#include <eirExe/Console.h>

class QtOpenCV;

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

public slots:
    void run();

private slots:
    void setupDefaults();
    void initOpenCV();

signals:
    void initFinished();

private:
    QtOpenCV * mpQtOpenCV=nullptr;
};

