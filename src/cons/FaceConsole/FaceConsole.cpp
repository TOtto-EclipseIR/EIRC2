#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
//#include <eirFinder/CascadeType.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirXfr/StartupDebug.h>
//#include <eirImageIO/BaseOutputDir.h>
//#include <eirImageIO/OutputManager.h>

//#include <eirRectFind/RectFinder.h>
//#include <eirMarker/MarkerManager.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(parent))
//    , cmpOutput(new OutputManager(parent))
//    , cmpRectFinder(new RectFinder(cmpConfigObject, parent))
  //  , cmpMarkerManager(new MarkerManager(cmpConfigObject, this))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);
    //TSTALLOC(cmpOutput);
    //TSTALLOC(cmpRectFinder);
  //  TSTALLOC(cmpMarkerManager);

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
    QTimer::singleShot(100, this, &FaceConsole::setupCommandLine);
}

void FaceConsole::enqueueNext()
{
    TRACEQFI << commandLine()->firstPositionalArgument();
//    TSTALLOC(cmpOutput);
    QString fileNameArgument = commandLine()->firstPositionalArgument();
//    if ( ! fileNameArgument.isEmpty())
  //      cmpOutput->enqueue(FramePak(rCommandLine().takePositionalArgument()));
}

void FaceConsole::setupCommandLine()
{
    TRACEFN
    rCommandLine().process();
    rCommandLine().expandDirectories();
    EMIT(commandLineSetup());
    QTimer::singleShot(100, this, &FaceConsole::setConfiguration);

}

void FaceConsole::setConfiguration()
{
    TRACEFN;
    cmpConfigObject->set(commandLine()->configuration());
    writeLine("---Configuration:");
    writeLines(commandLine()->configuration().dumpList());

    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    TRACE << baseDirString;
    EXPECT(mBaseOutputDir.mkpath(baseDirString));
    EXPECT(mBaseOutputDir.cd(baseDirString));
    EXPECT(mBaseOutputDir.exists());

    QString markedRectDirString(config()->
            configuration("Output/Dirs")
                .string("MarkedRect", "MarkedRect"));
    TRACE << markedRectDirString;
    QDir markedRectDir(markedRectDirString);
    QDir markedRectBaseDir = markedRectDir.isAbsolute() ? QDir::root() : mBaseOutputDir;
    QFileInfo markedRectDirFileInfo(markedRectBaseDir, markedRectDirString);
    if (markedRectDirFileInfo.exists())
    {
        EXPECTNOT(markedRectDirFileInfo.isFile());
        mMarkedRectOutputDir = markedRectDirFileInfo.dir();
    }
    else
    {
        mMarkedRectOutputDir = markedRectDirFileInfo.dir();
        EXPECT(mMarkedRectOutputDir.mkpath(markedRectDirString));
        EXPECT(mMarkedRectOutputDir.cd(markedRectDirString));
        EXPECT(mMarkedRectOutputDir.exists());
        if (mMarkedRectOutputDir.exists())
            writeLine("   " + mMarkedRectOutputDir.absolutePath() + " created");
    }
    DUMPVAL(mMarkedRectOutputDir);
    TODO(BackToImageIO);
    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QDir baseCascadeDir(config()->configuration("/Resources/RectFinder")
                 .string("BaseDir"));
    //cmpRectFinder->set(baseDir);
    QString cascadeFileName = config()->
            configuration("/Resources/RectFinder/PreScan")
                .string("XmlFile");
    QFileInfo cascadeFileInfo(baseCascadeDir, cascadeFileName);
    TRACE << cascadeFileInfo << cascadeFileInfo.exists()
          << cascadeFileInfo.isReadable() << cascadeFileInfo.isFile();
    EXPECT(cascadeFileInfo.exists());
    EXPECT(cascadeFileInfo.isReadable());
    EXPECT(cascadeFileInfo.isFile());
    write("---Cascade: "+cascadeFileInfo.absoluteFilePath()+" loading...");
    mPreScanCascade.loadCascade(cascadeFileInfo.absoluteFilePath());
    EXPECT(mPreScanCascade.isLoaded());
    //cmpRectFinder->load(CascadeType::PreScan, cascadeFileInfo.absoluteFilePath());
//    EXPECT(cmpRectFinder->loaded(CascadeType::PreScan));
    writeLine("done");
    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &FaceConsole::startProcessing);}

void FaceConsole::startProcessing()
{
    TRACEFN;

//    NEEDDO(cmpOutput->start());

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
//    Success success;
//    QByteArray bytes;
//    QImage image(mCurrentFileInfo.absoluteFilePath());
    QImage rectImage;
    QString outputFileName;

    writeLine("---Processing: "+mCurrentFileInfo.absoluteFilePath());
    MUSTDO(mPreScanCascade.configure);
    mPreScanCascade.imreadInputMat(mCurrentFileInfo);
    mCurrentRectangles = mPreScanCascade.detect();
    writeLine(QString("   %1 PreScan rectangles found")
                            .arg(mCurrentRectangles.size()));
    outputFileName = QQFileInfo(mMarkedRectOutputDir,
                        mCurrentFileInfo.completeBaseName()+"-%M@.png")
                                  .absoluteFilePath();
    writeLine("   " + mPreScanCascade.imwriteMarkedImage(outputFileName) + " written");
    EMIT(processed(QFileInfo(mCurrentFileInfo),
             mCurrentRectangles.size()));
    NEEDDO("somethingWithFramePak");
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
