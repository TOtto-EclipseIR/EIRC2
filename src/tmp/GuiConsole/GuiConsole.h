#pragma once

#include <QMainWindow>

#include <QGridLayout>

class GuiConsole : public QMainWindow
{
    Q_OBJECT
public:
    explicit GuiConsole(QWidget *parent = nullptr);

signals:

private:
    QGridLayout * const cmpMainLayout;

};

