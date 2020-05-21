// file: {eirC2 repo}./src/apps/cons/If2Console/INDIfaceConsole.h
#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QList>

#include <eirBase/VarPak.h>
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
    CommandLine * commandLine();

#ifdef EIRC2_IF2CONSOLE_TAKETWO23
public slots:
    void initializeApplication();

private slots:
    void initializeResources();
    void processCommandLine();

signals:
    void applicationInitd();
    void resoursesInitd();
    void commandLinePocessed();
    void pendingFilesSet();
    void fileDirsPendingNotEmpty();
    void inputDirEmpty();
    void inputScanned();
    void processingImage(QFileInfo qfi);
    void imageWritten(const QFileInfo qfi, QImage image);
    void imageProcessed(QFileInfo qfi);
    void processingComplete();

protected:

private:


private:
    FileInfoQueue * mpFileInfoQueue=nullptr;
    CommandLine * mpCommandLine=nullptr;

#else // TAKEONE
    void configure(const VarPak &config);
    QString configString(const MultiName &key) const;
    void setOutputDirs(const VarPak &config);
    QDir outputDir(QDir baseDir, QString dirName);
    void processInputImage(const QFileInfo & inFileInfo);
    static QImage toGrey(const QImage & inputImage);

    void scanInputDir();
    void nextImage();
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
