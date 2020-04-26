// file: {eirC2 repo}./src/apps/cons/If2Console/INDIfaceConsole.h
#pragma once


#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QList>

#include <eirBase/VarPak.h>
#include <eirType/QQRectList.h>
#include <eirType/Region.h>
#include <eirExe/Console.h>
#include <eirQtCV4/QtCVobjdetect.h>
#include <eirQtCV4/Detector.h>

class INDIfaceConsole : public Console
{
    Q_OBJECT
public:
    explicit INDIfaceConsole(Console *parent = nullptr);

protected:
    void configure(const VarPak &config);
    QString configString(const MultiName &key) const;
    QDir outputDir(const QDir &baseDir,
                   const MultiName &configKey);
    void processInputImage(const QFileInfo & inFileInfo);
    static QImage toGrey(const QImage & inputImage);
    void findFFRectangles(const Region region=Region());
    CommandLine * commandLine();

public slots:
    void initializeApplication();

private slots:
    void initializeResources();
    void processCommandLine();
    void setOutputDirs();
    void scanInputDir();
    void nextImage();

signals:
    void applicationInitd();
    void resoursesInitd();
    void pendingFilesSet();
    void inputDirEmpty();
    void inputScanned();
    void processingImage(QFileInfo qfi);
    void imageWritten(const QFileInfo qfi, QImage image);
    void imageProcessed(QFileInfo qfi);
    void processingComplete();

private:
    VarPak mConfiguration;
    QFileInfoList mPendingFiles;
    QDir mInputDir;
    QDir mBaseDir;
    QDir mGreyInputDir;
    QDir mMarkedRectangleDir;
    QDir mHeatmapDir;
    QtCVobjdetect * mpObjdetect=nullptr;
    Detector * mpFFDetector=nullptr;
    QQRectList mRectList;
};

