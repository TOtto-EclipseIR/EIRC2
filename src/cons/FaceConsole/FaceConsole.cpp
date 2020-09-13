#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
#include <eirImage/SimpleRectMarker.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(this))
    , cmpPreScanObjDet(new ObjectDetector(cvCascade::PreScan,
                                          cmpConfigObject, this))
    , mPreScanConfig("PreScanConfig")
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);
    TSTALLOC(cmpPreScanObjDet);
    cmpConfigObject->setObjectName("ConfigObject:FaceConsole");
    cmpPreScanObjDet->setObjectName("ObjectDetector:FaceConsole:PreScan");
    QTimer::singleShot(500, this, &FaceConsole::initializeApplication);
    TRACERTV();
}

ConfigObject *FaceConsole::config() const
{
    return cmpConfigObject;
}

void FaceConsole::initializeApplication()
{
    TRACEFN;
    QLocale locale;
    writeLine(QString("%1 %2 started %3")
              .arg(qApp->applicationName())
              .arg(qApp->applicationVersion())
              .arg(locale.toString(QDateTime::currentDateTime())));
    CONNECT(cmpPreScanObjDet, &ObjectDetector::ready,
            cmpPreScanObjDet, &ObjectDetector::start);
    CONNECT(this, &FaceConsole::processingStarted,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processed,
            this, &FaceConsole::nextFile);
    CONNECT(this, &FaceConsole::processingComplete,
            qApp, &QCoreApplication::quit);
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &FaceConsole::processCommandLine);
}

void FaceConsole::enqueueNext()
{
    TRACEQFI << commandLine()->firstPositionalArgument();
    QString fileNameArgument = commandLine()->firstPositionalArgument();
}

void FaceConsole::processCommandLine()
{
    TRACEFN
    rCommandLine().process();
    rCommandLine().expandDirectories();
    CommandLine::ExpandDirResultList edrl = rCommandLine().expandDirResults();
    if ( ! edrl.isEmpty())
    {
        writeLine("---Directories:");
        foreach (CommandLine::ExpandDirResult edr, edrl)
        {
            int k = 0;
            writeLine(QString("   %1. %2 %3 files from %4")
                      .arg(++k).arg(edr.dir.path())
                      .arg(edr.fileCount).arg(edr.firstFileName));
        }
    }
    EMIT(commandLineProcessed());
    QTimer::singleShot(100, this, &FaceConsole::setConfiguration);

}

void FaceConsole::setConfiguration()
{
    TRACEFN;
    cmpConfigObject->set(commandLine()->configuration());
    writeLine("---Configuration:");
    writeLines(commandLine()->configuration().dumpList());
    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::setBaseOutputDir);
}

void FaceConsole::setBaseOutputDir()
{
    TRACEFN;
    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    DUMPVAL(baseDirString);
    QDir baseDir(baseDirString);
    EXPECT(baseDir.mkpath("."));
    EXPECT(baseDir.cd("."));
    EXPECT(baseDir.exists());
    DUMPVAL(baseDir);
    DUMPVAL(baseDir.exists());
    if (baseDir.exists()) mBaseOutputDir = baseDir;
    EMIT(baseDirSet());
    QTimer::singleShot(100, this, &FaceConsole::setOutputDirs);
}

void FaceConsole::setOutputDirs()
{
    TRACEFN;

    bool created = false;
    mMarkedRectOutputDir.setNull(true);
    QString markedRectDirString(config()->
            configuration("Output/Dirs")
                .string("MarkedRect"));
    DUMPVAL(markedRectDirString);

    if (markedRectDirString.isEmpty())
    {
        // do nothing, leave mMarkedRectOutputDir null
    }
    else if (QDir::isRelativePath(markedRectDirString))
    {
        QDir relativeDir(mBaseOutputDir);
        DUMPVAL(relativeDir);
        if ( ! relativeDir.exists(markedRectDirString))
            created = relativeDir.mkpath(markedRectDirString);
        EXPECT(relativeDir.cd(markedRectDirString));
        DUMPVAL(relativeDir);
        EXPECT(relativeDir.exists());
        DUMPVAL(relativeDir.exists());
        if (relativeDir.exists())
            mMarkedRectOutputDir = relativeDir;
        // else mMarkedRectOutputDir is still null
    }
    else if (QDir::isAbsolutePath(markedRectDirString))
    {
        QDir absoluteDir(markedRectDirString);
        if ( ! absoluteDir.exists())
            created = absoluteDir.mkpath(".");
        if (absoluteDir.exists())
            mMarkedRectOutputDir = absoluteDir;
        // else mMarkedRectOutputDir is still null
    }
    else
    {
        writeErr(QString("***%1 Dir = %2 is invalid").arg("MarkedRect").arg(markedRectDirString));
    }

    DUMPVAL(mMarkedRectOutputDir.isNull());
    DUMPVAL(mMarkedRectOutputDir);
    if (mMarkedRectOutputDir.notNull())
        writeLine("---"+mMarkedRectOutputDir.absolutePath()
                  + (created ? " created" : " exists"));

    NEEDDO(OtherDirs);
    TODO(BackToImageIO);
    EMIT(outputDirsSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QDir baseCascadeDir(config()->configuration("/Resources/RectFinder")
                 .string("BaseDir"));
    QString preScanCascadeFileName = config()->
            configuration("/Resources/RectFinder/PreScan")
                .string("XmlFile");
    QFileInfo preScanCascadeFileInfo(baseCascadeDir, preScanCascadeFileName);
    TRACE << preScanCascadeFileInfo << preScanCascadeFileInfo.exists()
          << preScanCascadeFileInfo.isReadable() << preScanCascadeFileInfo.isFile();
    EXPECT(preScanCascadeFileInfo.exists());
    EXPECT(preScanCascadeFileInfo.isReadable());
    EXPECT(preScanCascadeFileInfo.isFile());
    write("---Cascade: "+preScanCascadeFileInfo.absoluteFilePath()+" loading...");
    cmpPreScanObjDet->cascade()->loadCascade(preScanCascadeFileInfo.absoluteFilePath());
    EXPECT(cmpPreScanObjDet->cascade()->isLoaded());
    EXPECT(cmpPreScanObjDet->cascade()->loadCoreSize(preScanCascadeFileInfo));
    EXPECT(cmpPreScanObjDet->cascade()->coreSize().isValid());

    mPreScanConfig += config()->configuration("Option/RectFinder");
    mPreScanConfig += config()->configuration("PreScan/RectFinder");
    mPreScanConfig.dump();
    writeLine(QString("done. Core=%1x%2")
            .arg(cmpPreScanObjDet->cascade()->coreSize().width())
            .arg(cmpPreScanObjDet->cascade()->coreSize().height()));
    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &FaceConsole::startProcessing);}

void FaceConsole::startProcessing()
{
    TRACEFN;

    NEEDDO(more);
    EMIT(processingStarted());
}

void FaceConsole::nextFile()
{
    TRACEQFI << commandLine()->positionalArgumentSize();
    if (commandLine()->positionalArgumentSize() > 0)
    {
        mCurrentFileInfo = QFileInfo(rCommandLine().takePositionalArgument());
        DUMPVAL(mCurrentFileInfo);
        QTimer::singleShot(100, this, &FaceConsole::processCurrentFile);
    }
    else
    {
        QTimer::singleShot(100, this, &FaceConsole::finishProcessing);
    }
}

void FaceConsole::processCurrentFile()
{
    TRACEQFI << mCurrentFileInfo << mCurrentFileInfo.isReadable();
    QString markedRectOutputFileName;

    //cmpPreScanObjDet->enqueue(mCurrentFileInfo);
    writeLine(QString("---Processing #%1: %2")
              .arg(commandLine()->takePositionalArgumentCount())
              .arg(mCurrentFileInfo.absoluteFilePath()));
#if 1
    mPreScanConfig.dump();
    Uuid pakUuid = cmpPreScanObjDet->process(mPreScanConfig, mCurrentFileInfo);
    mCurrentRectangles.set(cmpPreScanObjDet->pak(pakUuid).at("PreScan/Rectangles"));
    mCurrentResults.set(cmpPreScanObjDet->pak(pakUuid).at("PreScan/ResultList"));
    writeLine(QString("   %1 PreScan rectangles found, %2 candidate faces, %3 orphans")
            .arg(mCurrentRectangles.size())
            .arg(mCurrentResults.count()).arg(mCurrentResults.orphanCount()));
    markedRectOutputFileName = QQFileInfo(mMarkedRectOutputDir,
                        mCurrentFileInfo.completeBaseName()+"-%M@.png")
                                  .absoluteFilePath();
    markedRectOutputFileName.replace("%M", cmpPreScanObjDet->cascade()->methodString());
    QQImage inputImage = cmpPreScanObjDet->processInputImage();
    SimpleRectMarker rectMarker(inputImage);
    Configuration preScanMarkerConfig = cmpConfigObject->
            configuration("/Marker/MarkedPreScan");
    rectMarker.mark(preScanMarkerConfig, mCurrentResults, cmpPreScanObjDet->pak(pakUuid));
    QQImage rectMarkedImage = rectMarker;
    if (rectMarkedImage.save(markedRectOutputFileName))
        writeLine("   " + markedRectOutputFileName + " written");
    foreach (ObjDetResultItem item, mCurrentResults.list())
    {
        int ao = 1000 * item.averageOverlap();
        QString markedQuality = QString("Q%1-").arg(item.quality(), 3, 10, QChar('0'));
        QString markedFaceTitle = QString("-X%1Y%2W%3K%4O%5")
                .arg(item.resultRect().center().x(), 4, 10, QChar('0'))
                .arg(item.resultRect().center().y(), 4, 10, QChar('0'))
                .arg(item.resultRect().width(), 4, 10, QChar('0'))
                .arg(item.count(), 2, 10, QChar('0'))
                .arg(ao, 3, 10, QChar('0'));
        QFileInfo markedFaceInfo(mMarkedRectOutputDir,
            markedQuality + mCurrentFileInfo.completeBaseName() + markedFaceTitle + ".PNG");
        QQImage markedFaceImage = rectMarkedImage.copy(item.resultRect().expandedBy(2.0));
        if (markedFaceImage.save(markedFaceInfo.absoluteFilePath()))
            writeLine("   "+markedFaceInfo.absoluteFilePath()+" written");
    }
#endif
    EMIT(processed(QFileInfo(mCurrentFileInfo),
             mCurrentRectangles.size()));
    NEEDDO(processFailed());
    /*
    else
    {
        EMIT(processFailed(mCurrentFileInfo, "Error locating face objects"));
    }
    */
    NEEDDO(more);
}

void FaceConsole::finishProcessing()
{
    TRACEFN;
    writeLine("===Processing Complete");
    NEEDDO(more);
    EMIT(processingComplete());
}
