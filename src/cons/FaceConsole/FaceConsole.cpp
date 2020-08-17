#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
#include <eirType/Success.h>
#include <eirXfr/Debug.h>
#include <eirImageIO/BaseOutputDir.h>
#include <eirImageIO/OutputManager.h>

//#include <eirRectFind/RectFinder.h>
//#include <eirMarker/MarkerManager.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(parent))
    , cmpOutput(new OutputManager(parent))
    , cmpRectFinder(new RectFinder(cmpConfigObject, parent))
  //  , cmpMarkerManager(new MarkerManager(cmpConfigObject, this))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);
    TSTALLOC(cmpOutput);
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
    TSTALLOC(cmpOutput);
    QString fileNameArgument = commandLine()->firstPositionalArgument();
    if ( ! fileNameArgument.isEmpty())
        cmpOutput->enqueue(FramePak(rCommandLine().takePositionalArgument()));
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

    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));

    BaseOutputDir baseDir(baseDirString);
    cmpOutput->setBase(baseDir);
    cmpOutput->configure(cmpConfigObject);

    EMIT(configurationSet());
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);
}

void FaceConsole::initializeResources()
{
    TRACEFN;
    cmpRectFinder->configure(config()->configuration("/Option/RectFinder"));
    cmpRectFinder->configure("PreScan",
                             config()->configuration("/PreScan/RectFinder"));

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
    cmpRectFinder->load("PreScan", cascadeFileInfo.absoluteFilePath());
    BEXPECT(cmpRectFinder->loaded("PreScan"));

    EMIT(resoursesInitd());
 QTimer::singleShot(100, this, &FaceConsole::startProcessing);}

void FaceConsole::startProcessing()
{
    TRACEFN;

    NEEDDO(cmpOutput->start());

    NEEDDO(more);
    EMIT(processingStarted());
}

void FaceConsole::nextFile()
{
    TRACEFN;

    if (commandLine()->positionalArgumentSize())
    {
        mCurrentFile = QFileInfo(rCommandLine().takePositionalArgument());
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
    TRACEQFI << mCurrentFile << mCurrentFile.isReadable();
    Success success(true);
    QByteArray bytes;
    QImage image;
    QImage rectImage;
#if 1
    if (success) success = mFramePak.setInputFrame(mCurrentFile);
    if (success) cmpRectFinder->set("PreScan", image);
    if (success) cmpRectFinder->findRectangles("PreScan");
    if (success) mCurrentRectangles = cmpRectFinder->rectangleList("PreScan");
    if (success) rectImage = cmpRectFinder->makeRectImage();
    if (success) success = ! rectImage.isNull();
    if (success) mRectImage = rectImage;
    if (success) success = mRectImage.save(QFileInfo(
               QDir(config()->configuration("Output").string("BaseDir")),
               config()->configuration("Output/Dirs").string("PreScan"))
                                           .absoluteFilePath());
    if (success)
    {
        mFramePak.setPreScanImage(cmpRectFinder->findRectImage("PreScan"));
        mFramePak.setFrameRectangles(mCurrentRectangles);
        EMIT(processed(QFileInfo(mCurrentFile),
             mCurrentRectangles.size()));
        NEEDDO("somethingWithFramePak");
    }
    else
    {
        EMIT(processFailed(mCurrentFile, "Error locating face objects"));
    }
#else
    if (success) success = mCurrentFile.isReadable();
    if (success) file->setFileName(mCurrentFile
                        .absoluteFilePath());
    if (success) success = file->open(QIODevice::ReadOnly);
    if (success) success = QFileDevice::NoError == file->error();
    if (success) success = file->size() < 1024;
    if (success) bytes = file->readAll();
    if (success) success = file->size() == bytes.size();
    if ( ! success)
    {
        EMIT(processFailed(mCurrentFile,
            file->errorString().isEmpty()
                           ? "Error opening to read"
                           : file->errorString()));
        return;
    }
    if (success) image = QImage::fromData(bytes);
    if (success) success = image.isNull();
    if (success) cmpRectFinder->set(image);
    if (success) cmpRectFinder->findRectangles("PreScan");
    if (success) mCurrentRectangles = cmpRectFinder->rectangleList("PreScan");
    if ( ! success)
    {
        EMIT(processFailed(mCurrentFile, "Error locating face objects"));
        return;
    }
    mFramePak.setInputFrame(mCurrentFile.absoluteFilePath());
#endif
    NEEDDO(more);
    EMIT(processed(mCurrentFile, 0));
}

void FaceConsole::finishProcessing()
{
    TRACEFN;


    NEEDDO(more);
    EMIT(processingComplete());
}
