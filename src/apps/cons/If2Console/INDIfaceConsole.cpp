#include "INDIfaceConsole.h"

#include <QImage>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/Settings.h>
#include <eirQtCV/eirQtCV.h>
#include <eirQtCV/QtOpenCV.h>


INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
{
    TRACEFN
    setObjectName("INDIfaceConsole");
}

void INDIfaceConsole::run()
{
    TRACEFN
    writeLine("Welcome to INDIfaceConsole");
/*    CONNECT(this, &ApplicationHelper::initFinished,
            this, &INDIfaceConsole::initSettings);
    CONNECT(this, &INDIfaceConsole::frameProcessingComplete,
            qApp, &QCoreApplication::quit);
*/    QTimer::singleShot(100, this,
                       &ApplicationHelper::run);
}
#if 0
void INDIfaceConsole::load()
{
    TRACEFN
    TSTALLOC(mpQtOpenCV);
    mpQtOpenCV->setObjectLoadTypes(QtOpenCV::FrontalFace);
    mpQtOpenCV->startCascadeLoad();
}

void INDIfaceConsole::scanFiles()
{
    TRACEFN
    QDir dir("/INDIface/INDIin/If2Console");
    mPendingFiles << dir.entryInfoList(eirQtCV::imageReadNameFilters(),
                                       QDir::Files);
    emit fileScanComplete();
}

void INDIfaceConsole::processNextFrame()
{
    TRACEFN
    if (mPendingFiles.isEmpty())
    {
        emit frameProcessingComplete();
        return;
    }
    TSTALLOC(mpQtOpenCV);
    QFileInfo qfi = mPendingFiles.takeFirst();
    QImage inputFrame(qfi.filePath());
    TRACE << qfi << inputFrame.size() << inputFrame.format();
    // mpQtOpenCV->setInputImage(QtOpenCV::FrontalFace, inputFrame);
    // emit frameProcessed();
}


void INDIfaceConsole::initSettings()
{
    TRACEFN

    QTimer::singleShot(100, this,
                       &INDIfaceConsole::setupDefaults);

}

void INDIfaceConsole::setupDefaults()
{
    TRACEFN

    QTimer::singleShot(100, this,
                       &INDIfaceConsole::initOpenCV);
}

void INDIfaceConsole::initOpenCV()
{
    TRACEFN
    mpQtOpenCV = new QtOpenCV(this);
    TSTALLOC(mpQtOpenCV)
    CONNECT(mpQtOpenCV, &QtOpenCV::overideConfigurationLoaded,
            this, &INDIfaceConsole::load);
    CONNECT(mpQtOpenCV, &QtOpenCV::cascadeLoadFinished,
            this, &INDIfaceConsole::scanFiles);
    CONNECT(this, &INDIfaceConsole::fileScanComplete,
            this, &INDIfaceConsole::processNextFrame);
    CONNECT(this, &INDIfaceConsole::frameProcessed,
            this, &INDIfaceConsole::processNextFrame);
    emit initFinished();
}
#endif
