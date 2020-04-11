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
    void initSettings();
    void setupDefaults();
    void initOpenCV();
    void load();
    void scanFiles();
    void processNextFrame();

signals:
    void initFinished();
    void fileScanComplete();
    void frameProcessed();
    void frameProcessingComplete();

private:
    Settings * mpSettings=nullptr;
    QtOpenCV * mpQtOpenCV=nullptr;
    QFileInfoList mPendingFiles;
};

