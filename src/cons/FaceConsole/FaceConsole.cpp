#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(this))
    , cmpPreScanObjDet(new ObjectDetector(cvCascade::PreScan, this))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);

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
    mPreScanCascade.loadCascade(preScanCascadeFileInfo.absoluteFilePath());
    EXPECT(mPreScanCascade.isLoaded());

    Configuration preScanConfig = config()->configuration("Option/RectFinder");
    preScanConfig += config()->configuration("PreScan/RectFinder");
    NEEDDO(mPreScanCascade.configure);
    //mPreScanCascade.configure(preScanConfig);

    writeLine("done");
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
    QImage rectImage;
    QString markedRectOutputFileName;

    cmpPreScanObjDet->enqueue(mCurrentFileInfo);
    writeLine(QString("---Processing #%1: %2")
              .arg(commandLine()->takePositionalArgumentCount())
              .arg(mCurrentFileInfo.absoluteFilePath()));
#if 0
    mPreScanCascade.imreadInputMat(mCurrentFileInfo);
    mCurrentRectangles = mPreScanCascade.detect();
    writeLine(QString("   %1 PreScan rectangles found")
                            .arg(mCurrentRectangles.size()));
    markedRectOutputFileName = QQFileInfo(mMarkedRectOutputDir,
                        mCurrentFileInfo.completeBaseName()+"-%M@.png")
                                  .absoluteFilePath();
    markedRectOutputFileName.replace("%M", mPreScanCascade.methodString());
    if (mPreScanCascade.imwriteMarkedImage(markedRectOutputFileName))
        writeLine("   " + markedRectOutputFileName + " written");
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
