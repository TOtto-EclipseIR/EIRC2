#include "GuiConsole.h"

#include <QtDebug>

GuiConsole::GuiConsole(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << Q_FUNC_INFO;
    connect(this, &GuiConsole::ctord,
            this, &GuiConsole::setupConnections);
    setObjectName("GuiConsole");
    emit ctord();
}

void GuiConsole::setupConnections()
{
    qDebug() << Q_FUNC_INFO;
    connect(this, &GuiConsole::connectionsSetup,
            this, &GuiConsole::setupLayout);
    connect(this, &GuiConsole::layoutSetup,
            this, &GuiConsole::setupActions);
    connect(this, &GuiConsole::layoutSetup, mpStdoutConsole, &ConsoleWidget::setup);
    connect(this, &GuiConsole::layoutSetup, mpStderrConsole, &ConsoleWidget::setup);
    connect(this, &GuiConsole::layoutSetup, mpQtDebugConsole, &ConsoleWidget::setup);
    connect(this, &GuiConsole::actionsSetup,
            this, &GuiConsole::setupMenus);
    connect(this, &GuiConsole::menusSetup,
            this, &GuiConsole::setupToolbars);
    connect(this, &GuiConsole::toolbarsSetup,
            this, &GuiConsole::finishSetup);
    connect(this, &GuiConsole::currentDirChanged,
            this, &GuiConsole::changeCurrentDir);
    emit connectionsSetup();
}

void GuiConsole::setupLayout()
{
    qDebug() << Q_FUNC_INFO;
    mCurrentDir = QDir::current();
    mpMainWidget = new QWidget;
    mpMainLayout = new QGridLayout;
    mpMainWidget->setObjectName("MainLayout");
    mpMainLayout->setObjectName("MainLayout");
    mpStdoutConsole = new ConsoleWidget("stdout", ConsoleWidget::Stdout);
    mpStderrConsole = new ConsoleWidget("stderr", ConsoleWidget::Stderr);
    mpQtDebugConsole = new ConsoleWidget("QtDebug", ConsoleWidget::QtDebug);
    mCurrentDirFont.setFamily("Courier");
    mCurrentDirFont.setPointSize(10);
    mpCurrentDirLabel = new QLabel(mCurrentDir.absolutePath());
    mpCurrentDirLabel->setTextFormat(Qt::TextFormat::PlainText);
    mpCurrentDirLabel->setFont(mCurrentDirFont);
    mpStdinLine = new QLineEdit("stdin");
    mpHistoryCombo = new QComboBox;
    mpStdoutConsole->setObjectName("StdoutText");
    mpStderrConsole->setObjectName("StderrText");
    mpQtDebugConsole->setObjectName("QtDebugText");
    mpCurrentDirLabel->setObjectName("CurrentDirLabel");
    mpStdinLine->setObjectName("StdinLine");
    mpHistoryCombo->setObjectName("HistoryCombo");
    mpMainLayout->addWidget(mpStdoutConsole);
    mpMainLayout->addWidget(mpStderrConsole);
    mpMainLayout->addWidget(mpQtDebugConsole);
    mpMainLayout->addWidget(mpCurrentDirLabel);
    mpMainLayout->addWidget(mpStdinLine);
    mpMainLayout->addWidget(mpHistoryCombo);
    mpMainWidget->setLayout(mpMainLayout);
    QMainWindow::setCentralWidget(mpMainWidget);
    emit layoutSetup();
}

void GuiConsole::setupActions()
{
    qDebug() << Q_FUNC_INFO;
    emit actionsSetup();
}

void GuiConsole::setupMenus()
{
    qDebug() << Q_FUNC_INFO;
    emit menusSetup();
}

void GuiConsole::setupToolbars()
{
    qDebug() << Q_FUNC_INFO;
    emit toolbarsSetup();
}

void GuiConsole::finishSetup()
{
    qDebug() << Q_FUNC_INFO;
    emit setupFinished();
}

void GuiConsole::changeCurrentDir(const QDir &newCurrentDir)
{
    qDebug() << Q_FUNC_INFO;
    mpCurrentDirLabel->setText(newCurrentDir.absolutePath())    ;
}
