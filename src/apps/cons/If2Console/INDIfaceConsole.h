#pragma once

#include <QObject>
#include <eirExe/Console.h>

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

public slots:
    void run();

signals:

};

