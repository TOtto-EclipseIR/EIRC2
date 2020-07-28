#include "FaceConsole.h"

#include <QDateTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTimer>

#include <eirExe/CommandLine.h>
#include <eirExe/ConfigObject.h>
#include <eirXfr/Debug.h>
#include <eirRectFind/RectFinder.h>

FaceConsole::FaceConsole(QObject *parent)
    : Console(parent)
    , cmpConfig(new ConfigObject(parent))
    , cmpRectFinder(new RectFinder(parent))
{
    TRACEFN;
    setObjectName("FaceConsole");
    TSTALLOC(cmpConfig);
    TSTALLOC(cmpRectFinder);

    QTimer::singleShot(500, this, &FaceConsole::initializeApplication);
    TRACERTV();
}

ConfigObject *FaceConsole::config() const
{
    return cmpConfig;
}

void FaceConsole::initializeApplication()
{
    TRACEFN;
    QLocale locale;
    writeLine(QString("%1 %2 started %3")
              .arg(qApp->applicationName())
              .arg(qApp->applicationVersion())
              .arg(locale.toString(QDateTime::currentDateTime())));
    //cmpParser->addOption(QCommandLineOption(QStringList()
    //<< "exit" << "batch" << "x"));
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

    cmpConfig->set(commandLine()->configuration());

    QString baseDirString(config()->configuration("/Output").string("BaseDir"));
    QString rectDirString(config()->configuration("/PreScan/Face/Output").string("RectDir"));

    baseDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    rectDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    mBaseDir = QDir(baseDirString);

    if ( ! rectDirString.isEmpty())
    {
        mRectDir = mBaseDir;
        mRectDir.mkpath(rectDirString);
        mRectDir.cd(rectDirString);
    }
    TRACE << baseDirString << rectDirString
      << mRectDir.absolutePath();

    QTimer::singleShot(100, this, &FaceConsole::initializeResources);

}

void FaceConsole::initializeResources()
{
    TRACEFN;



    QFileInfo faceCascadeFileInfo(
                QDir(config()->configuration("/Resources/ObjDet").string("BaseDir")),
                config()->configuration("/PreScan/Resources/ObjDet/Face").string("XmlFile"));
    TRACE << faceCascadeFileInfo.absoluteFilePath()
          << faceCascadeFileInfo.exists()
          << faceCascadeFileInfo.isReadable();

}

void FaceConsole::startProcessing()
{

}
