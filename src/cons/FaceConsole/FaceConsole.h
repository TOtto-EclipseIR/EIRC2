#pragma once

#include <QObject>
#include <eirExe/Console.h>

class QCommandLineParser;
class ConfigObject;

class FaceConsole : public Console
{
    Q_OBJECT
public:
    explicit FaceConsole(QObject *parent = nullptr);
    ConfigObject *config() const;

public slots:
    void initializeApplication();

private slots:
    void setupCommandLine();
    void setConfiguration();
    void initializeResources();
    void startProcessing();

signals:
    void applicationInitd();
    void commandLineSetup();
    void configurationSet();
    void resoursesInitd();
    void processingStarted();

private:
    ConfigObject * const cmpConfig=nullptr;
    QDir mBaseDir;
    QDir mRectDir;
};

