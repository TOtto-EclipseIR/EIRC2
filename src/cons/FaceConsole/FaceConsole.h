#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <eirQtCV/cvCascade.h>
//#include <eirFinder/RectFinder.h>
//#include <eirFrame/FramePak.h>
//#include <eirImageIO/OutputManager.h>

class QCommandLineParser;
class ConfigObject;
class OutputManager;
// class MarkerManager;

class FaceConsole : public Console
{
    Q_OBJECT
public:
    explicit FaceConsole(QObject *parent = nullptr);
    ConfigObject *config() const;

public slots:
    void initializeApplication();
    void enqueueNext();

private slots:
    void setupCommandLine();
    void setConfiguration();
    void setBaseOutputDir();
    void setOutputDirs();
    void initializeResources();
    void startProcessing();
    void nextFile();
    void processCurrentFile();
    void finishProcessing();

signals:
    void applicationInitd();
    void commandLineSetup();
    void configurationSet();
    void baseDirSet();
    void outputDirsSet();
    void resoursesInitd();
    void processingStarted();
    void processed(QFileInfo fileInfo, int rectCount);
    void processFailed(QFileInfo fileInfo, QString errorString);
    void processingComplete();

private:
    ConfigObject * const cmpConfigObject=nullptr;
//    OutputManager * const cmpOutput=nullptr;
//    RectFinder * const cmpRectFinder=nullptr;
    cvCascade mPreScanCascade;
    QDir mBaseOutputDir;
    QDir mMarkedRectOutputDir;
    QFileInfo mCurrentFileInfo;
    QList<QRect> mCurrentRectangles;
//    FramePak mFramePak;
    QImage mRectImage;

  //  MarkerManager * const cmpMarkerManager=nullptr;
};

