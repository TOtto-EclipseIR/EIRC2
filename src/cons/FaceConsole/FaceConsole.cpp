#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
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
//    TSTALLOC(cmpRectFinder);
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
    QDir baseDir(config()->configuration("/Resources/RectFinder").string("BaseDir"));
    cmpRectFinder->set(baseDir);
    NEEDDO(exists-readable);

    cmpRectFinder->configure(config()->configuration("/Option/RectFinder"));

    cmpRectFinder->configure("PreScan",
                             config()->configuration("/PreScan/RectFinder"));
    cmpRectFinder->load("PreScan", config()->configuration("/Resources/RectFinder/PreScan/XmlFile").string("XmlFile"));
    BEXPECT(cmpRectFinder->loaded("PreScan"));

    EMIT(resoursesInitd());
 QTimer::singleShot(100, this, &FaceConsole::startProcessing);}

void FaceConsole::startProcessing()
{
    TRACEFN;

    cmpOutput->start();

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
    TRACEFN;


    NEEDDO(more);
    EMIT(processed(mCurrentFile, 0));
}

void FaceConsole::finishProcessing()
{
    TRACEFN;


    NEEDDO(more);
    EMIT(processingComplete());
}
