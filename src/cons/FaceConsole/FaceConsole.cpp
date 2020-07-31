#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
#include <eirXfr/Debug.h>
//#include <eirRectFind/RectFinder.h>
//#include <eirMarker/MarkerManager.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfigObject(new ConfigObject(parent))
//    , cmpRectFinder(new RectFinder(cmpConfigObject, parent))
  //  , cmpMarkerManager(new MarkerManager(cmpConfigObject, this))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfigObject);
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
//    cmpMarkerManager->setBaseDir(baseDirString);
  //  TRACE << cmpMarkerManager->baseDir();
    QTimer::singleShot(100, this, &FaceConsole::initializeResources);

}

void FaceConsole::initializeResources()
{
    TRACEFN;
    QDir baseDir(config()->configuration("/Resources/RectFinder").string("BaseDir"));
    NEEDDO(exists-readable);
//    cmpRectFinder->set(baseDir);



  //  cmpRectFinder->load("PreScan", config()->configuration("/Resources/RectFinder/PreScan").string("XmlFile"));
//    BEXPECT(cmpRectFinder->loaded("PreScan"));
}

void FaceConsole::startProcessing()
{

}
