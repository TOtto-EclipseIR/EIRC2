// file: {eirC2 repo}./src/apps/cons/If2Console/INDIfaceConsole.h
#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QList>

#include <eirBase/VarPak.h>
#include <eirType/QQFileInfo.h>
#include <eirType/QQFileInfoList.h>
#include <eirType/QQRectList.h>
#include <eirType/Region.h>
#include <eirExe/ApplicationHelper.h>

class CommandLine;
class FileInfoQueue;

#include "../../version.h"

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

#ifdef EIRC2_IF2CONSOLE_TAKETWO23
public slots:
    void initializeApplication();

private slots:
    void setupCommandLine();
    void setConfiguration();
    void initializeResources();
    void startProcessing();
    void nextFile();
    void processFile();
    void finishProcessing();

signals:
    void applicationInitd();
    void commandLineSetup();
    void configurationSet();
    void resoursesInitd();
    void processingStarted();
    void processingImage(QFileInfo qfi);
    void imageWritten(const QFileInfo qfi, QImage image);
    void imageProcessed(QFileInfo qfi);
    void processingComplete();

protected:
private:
private:
//    FileInfoQueue * mpFileInfoQueue=nullptr;
    CommandLineClientInterface * mpCommandLineInterface=nullptr;
    ConfigObject * mpConfig=nullptr;
    QQFileInfoList mImageFileQueue;
    QQFileInfo mCurrentImageFile;

#else // TAKEONE
protected slots:
    void configure(const VarPak &config);
    void setOutputDirs(const VarPak &config);
    void processInputImage(const QFileInfo & inFileInfo);
    void scanInputDir();
    void nextImage();

protected:
    QString configString(const MultiName &key) const;
    QDir outputDir(QDir baseDir, QString dirName);
    static QImage toGrey(const QImage & inputImage);

signals:
    void pendingFilesSet();
    void fileDirsPendingNotEmpty();
    void inputDirEmpty();
    void inputScanned();

private:
    CommandLine * mpCommandLine=nullptr;
    VarPak mConfiguration;
    QDir mInputDir;
    QDir mBaseDir;
    QDir mCapture2Dir;
    QDir mGreyInputDir;
    QDir mMarkedDetectDir;
    QDir mMarkedFaceDir;
    QDir mFaceDetectDir;
    QDir mMarkedRectangleDir;
    QDir mMarkedCandidateDir;
    QDir mHeatmapDir;
    QQRectList mRectList;
#endif
};
