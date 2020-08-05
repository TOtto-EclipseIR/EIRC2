#include "OutputManager.h"

#include <QRegularExpression>
#include <QTimer>

#include <eirXfr/Debug.h>

OutputManager::OutputManager(QObject *parent)
    : QObject(parent)
    , cmpTimer(new QTimer(this))
    , mTimerMSec(10)
{
    TRACEQFI << QOBJNAME(parent) << mTimerMSec;

}

OutputManager::OutputManager(const Milliseconds timerMSec, QObject *parent)
    : QObject(parent)
    , cmpTimer(new QTimer(this))
    , mTimerMSec(timerMSec)
{
    TRACEQFI << QOBJNAME(parent) << mTimerMSec;

}

void OutputManager::setBase(const QDir &baseDir)
{
    TRACEQFI << baseDir;
    mBaseDir = baseDir;
}

OutputManager::~OutputManager()
{
    if (cmpTimer)
    {
        cmpTimer->stop();
        delete cmpTimer;
    }
}

void OutputManager::configure(ConfigObject *cfgObj)
{
    TRACEFN;
//    BasicName::List outputDirs = mOutputConfig.groupKeys("Output");
    mOutputConfig = cfgObj->configuration("/Output/Dirs");
    mMarkerConfig = cfgObj->configuration("/Marker");
    mOutputConfig.setName("OutputConfig");
    mMarkerConfig.setName("MarkerConfig");
    mOutputConfig.dump();
    mMarkerConfig.dump();
}

void OutputManager::start(const Milliseconds msec)
{
    TRACEQFI << msec << mTimerMSec;
    TSTALLOC(cmpTimer);
    if (msec) mTimerMSec = msec;
    CONNECT(cmpTimer, &QTimer::timeout,
            this, &OutputManager::pulse);
    cmpTimer->setSingleShot(false);
    cmpTimer->start(mTimerMSec);
}

void OutputManager::pulse()
{
    TRACEFN;
    MUSTDO(it);
}

void OutputManager::enqueue(FramePak incomingFP)
{
    TRACEQFI << incomingFP();
    MUSTUSE(incomingFP);
}

void OutputManager::startMarkNext()
{
    TRACEFN;
    MUSTDO(it);
}

void OutputManager::markNext()
{
    TRACEFN;
    MUSTDO(it);
}

void OutputManager::markComplete(FramePak markedFP)
{
    TRACEQFI << markedFP();
    MUSTUSE(markedFP);
    MUSTDO(it);

}

void OutputManager::enqueueMarked(FramePak markedFP)
{
    TRACEQFI << markedFP();
    MUSTUSE(markedFP);
    MUSTDO(it);

}

void OutputManager::splitMarked()
{
    TRACEFN;
    MUSTDO(it);

}


