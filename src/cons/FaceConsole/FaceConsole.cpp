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
    , cmpRectFinder(new RectFinder(cmpConfigObject, parent))
  //  , cmpMarkerManager(new MarkerManager(cmpConfigObject, this))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);
    //TSTALLOC(cmpOutput);
    TSTALLOC(cmpRectFinder);
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
#if 1
    EXPECT(mBaseOutputDir.mkpath(baseDirString));
    EXPECT(mBaseOutputDir.cd(baseDirString));
    EXPECT(mBaseOutputDir.exists());

    QString markedRectDirString(config()->
            configuration("Output/Dirs")
                .string("MarkedRect", "MarkedRect"));
    mMarkedRectOutputDir = mBaseOutputDir;
    EXPECT(mMarkedRectOutputDir.mkpath(markedRectDirString));
    EXPECT(mMarkedRectOutputDir.cd(markedRectDirString));
    EXPECT(mMarkedRectOutputDir.exists());
    if (mMarkedRectOutputDir.exists())
        writeLine("   " + mMarkedRectOutputDir.absolutePath() + "created");

    TODO(BackToImageIO);
#else
    BaseOutputDir baseDir(baseDirString);
    cmpOutput->setBase(baseDir);
    cmpOutput->configure(cmpConfigObject);
#endif
    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QDir baseDir(config()->configuration("/Resources/RectFinder")
                 .string("BaseDir"));
    cmpRectFinder->set(baseDir);
    QString cascadeFileName = config()->
            configuration("/Resources/RectFinder/PreScan")
                .string("XmlFile");
    QFileInfo cascadeFileInfo(baseDir, cascadeFileName);
    TRACE << cascadeFileInfo << cascadeFileInfo.exists()
          << cascadeFileInfo.isReadable() << cascadeFileInfo.isFile();
    EXPECT(cascadeFileInfo.exists());
    EXPECT(cascadeFileInfo.isReadable());
    EXPECT(cascadeFileInfo.isFile());
    cmpRectFinder->load(CascadeType::PreScan, cascadeFileInfo.absoluteFilePath());
//    BEXPECT(cmpRectFinder->loaded(CascadeType::PreScan));
    writeLine("---Cascade: "+cascadeFileInfo.absoluteFilePath()+" loaded");

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
    TRACEFN;

    if (commandLine()->positionalArgumentSize())
    {
        mCurrentFileInfo = QFileInfo(rCommandLine().takePositionalArgument());
        DUMPVAL(mCurrentFileInfo);
        QTimer::singleShot(100, this, &FaceConsole::processCurrentFile);
    }
    else
    {
        QTimer::singleShot(100, this, &FaceConsole::nextFile);
    }

    NEEDDO(more);
    EMIT(processed(QFileInfo(), 0));
}

void FaceConsole::processCurrentFile()
{
    TRACEQFI << mCurrentFileInfo << mCurrentFileInfo.isReadable();
    Success success;
//    QByteArray bytes;
    QImage image(mCurrentFileInfo.absoluteFilePath());
    QImage rectImage;
    QString outputFileName;

    //if (success) success = mFramePak.setInputFrame(mCurrentFile);
    writeLine("---Processing: "+mCurrentFileInfo.absoluteFilePath());
    TRACE << image.size() << image.format();
    success = ! image.isNull();
    EXPECT(success);
    if (success) cmpRectFinder->set(CascadeType::PreScan, image);
    EXPECT(success);
    if (success) cmpRectFinder->findRectangles(CascadeType::PreScan);
    EXPECT(success);
    if (success) mCurrentRectangles = cmpRectFinder->rectangleList(CascadeType::PreScan);
    EXPECT(success);
    if (success) writeLine(QString("   %1 PreScan rectangles found")
                            .arg(mCurrentRectangles.size()));
    if (success) rectImage = cmpRectFinder->makeRectImage(CascadeType::PreScan);
    EXPECT(success);
    if (success) success = ! rectImage.isNull();
    EXPECT(success);
    if (success) mRectImage = rectImage;
    EXPECT(success);
    if (success) outputFileName = QFileInfo(mMarkedRectOutputDir,
                                            mCurrentFileInfo.completeBaseName()+".PNG")
                                  .absoluteFilePath();
    EXPECT(success);
    if (success) success = mRectImage.save(outputFileName);
    EXPECT(success);
    if (success) writeLine("   " + outputFileName + " written");
    EXPECT(success);
    if (success)
    {
        //mFramePak.setPreScanImage(cmpRectFinder->findRectImage(CascadeType::PreScan));
        //mFramePak.setFrameRectangles(mCurrentRectangles);
        EMIT(processed(QFileInfo(mCurrentFileInfo),
             mCurrentRectangles.size()));
        NEEDDO("somethingWithFramePak");
    }
    else
    {
        EMIT(processFailed(mCurrentFileInfo, "Error locating face objects"));
    }
    NEEDDO(more);
    EMIT(processed(mCurrentFileInfo, 0));
}

void FaceConsole::finishProcessing()
{
    TRACEFN;


    NEEDDO(more);
    EMIT(processingComplete());
}
