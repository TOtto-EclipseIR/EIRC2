// file: {eirC2 repo}./src/apps/cons/If2Console/INDIfaceConsole.h
#pragma once

#include <QObject>
#include <eirExe/Console.h>

#include <QDir>
#include <QFileInfo>
#include <QList>

#include <eirBase/VarPak.h>
#include <eirType/QQRectList.h>
#include <eirType/Region.h>
#include <eirExe/ApplicationHelper.h>
#include <eirQtCV4/QtCVobjdetect.h>
#include <eirQtCV4/Detector.h>

class CommandLine;
class FileInfoQueue;

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

protected:
    void configure(const VarPak &config);
    QString configString(const MultiName &key) const;
    void setOutputDirs(const VarPak &config);
    QDir outputDir(QDir baseDir, QString dirName);
    void processInputImage(const QFileInfo & inFileInfo);
    static QImage toGrey(const QImage & inputImage);
    void findFFRectangles(const Region region=Region());
    CommandLine * commandLine();

public slots:
    void initializeApplication();

private slots:
    void initializeResources();
    void processCommandLine();
    void scanInputDir();
    void nextImage();

signals:
    void applicationInitd();
    void resoursesInitd();
    void pendingFilesSet();
    void fileDirsPendingNotEmpty();
    void inputDirEmpty();
    void inputScanned();
    void processingImage(QFileInfo qfi);
    void imageWritten(const QFileInfo qfi, QImage image);
    void imageProcessed(QFileInfo qfi);
    void processingComplete();

private:
    FileInfoQueue * mpFileInfoQueue=nullptr;
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
    QtCVobjdetect * mpObjdetect=nullptr;
    Detector * mpFFDetector=nullptr;
    QQRectList mRectList;
};
