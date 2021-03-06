#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <eirType/QQDir.h>
#include <eirObjDet/ObjectDetector.h>
#include <eirQtCV/cvCascade.h>  // TODO: Remove for Flight

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
    void enqueueNext();

private slots:
    void processCommandLine();
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
    void commandLineProcessed();
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
    ObjectDetector * const cmpPreScanObjDet=nullptr;
    //cvCascade mPreScanCascade;
    Configuration mPreScanConfig;
    QDir mBaseOutputDir;
    QQDir mMarkedRectOutputDir;
    QQFileInfo mCurrentFileInfo;
    QQRectList mCurrentRectangles;
    ObjDetResultList mCurrentResults;
    QImage mRectImage;
};

