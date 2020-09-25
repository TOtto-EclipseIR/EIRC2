#pragma once

#include <QMainWindow>

#include <QAction>
#include <QComboBox>
#include <QDir>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>

#include "ConsoleWidget.h"

class GuiConsole : public QMainWindow
{
    Q_OBJECT
public:
    explicit GuiConsole(QWidget *parent = nullptr);

private slots:
    void setupLayout();
    void setupConnections();
    void setupActions();
    void setupMenus();
    void setupToolbars();
    void finishSetup();

    void changeCurrentDir(const QDir &newCurrentDir);

signals:
    void ctord();
    void layoutSetup();
    void connectionsSetup();
    void actionsSetup();
    void menusSetup();
    void toolbarsSetup();
    void setupFinished();

    void currentDirChanged(const QDir &newCurrentDir);

private:
    QWidget * mpMainWidget=nullptr;
    QGridLayout * mpMainLayout=nullptr;
    ConsoleWidget * mpStdoutConsole=nullptr;
    ConsoleWidget * mpStderrConsole=nullptr;
    ConsoleWidget * mpQtDebugConsole=nullptr;
    QLabel * mpCurrentDirLabel=nullptr;
    QLineEdit * mpStdinLine=nullptr;
    QComboBox * mpHistoryCombo=nullptr;
    QDir mCurrentDir;
    QFont mCurrentDirFont;

    QAction * mpExitAct=nullptr;

};

