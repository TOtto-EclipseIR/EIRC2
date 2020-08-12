#include "OutputManager.h"

#include <QRegularExpression>
#include <QTimer>

#include <eirXfr/Debug.h>

OutputManager::OutputManager(QObject *parent)
    : QObject(parent)
    , cmpTimer(new QTimer(this))
    , mTimerMsec(10)
{
    TRACEQFI << QOBJNAME(parent) << mTimerMsec;

}

OutputManager::OutputManager(const Milliseconds timerMSec, QObject *parent)
    : QObject(parent)
    , cmpTimer(new QTimer(this))
    , mTimerMsec(timerMSec)
{
    TRACEQFI << QOBJNAME(parent) << mTimerMsec;

}

void OutputManager::setBase(const QDir &baseDir)
{
    TRACEQFI << baseDir;
    mBaseDir = baseDir;
}

int OutputManager::incomingQueueSize() const
{
    return mIncomingQueue.size();
}

bool OutputManager::incomingEmpty() const
{
    return mIncomingQueue.isEmpty();
}

FramePak OutputManager::firstIncoming() const
{
    TRACEQFI << incomingQueueSize()
             << (incomingQueueSize() ? mIncomingQueue.first()
                                     : FramePak()).toString();
    return incomingQueueSize() ? mIncomingQueue.first()
                                : FramePak();
}

FramePak OutputManager::takeIncoming()
{
    TRACEQFI << incomingQueueSize()
             << (incomingQueueSize() ? mIncomingQueue.first()
                                     : FramePak()).toString();
    return (incomingQueueSize() ? mIncomingQueue.takeFirst()
                                : FramePak());
}

bool OutputManager::incomingNotEmpty() const
{
    return ! incomingEmpty();
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
    TRACEQFI << msec << mTimerMsec;
    TSTALLOC(cmpTimer);
    if (msec) mTimerMsec = msec;
    CONNECT(cmpTimer, &QTimer::timeout,
            this, &OutputManager::pulse);
    cmpTimer->setSingleShot(false);
    cmpTimer->start(mTimerMsec);
    EMIT(started(mTimerMsec));
}

void OutputManager::pulse()
{
    TRACEFN;
    MUSTDO(it);
    EMIT(pulsed());
}

void OutputManager::enqueue(FramePak incomingFP)
{
    TRACEQFI << incomingFP() << incomingQueueSize();
    mIncomingQueue << incomingFP;
    EMIT(incomingSize(incomingQueueSize()));
}

void OutputManager::startMarkNext()
{
    TRACEFN;
    mCurrentFP = takeIncoming();
    NEEDDO(more);
}

void OutputManager::markNext()
{
    TRACEFN;
    NEEDDO(more);
}

void OutputManager::markComplete()
{
    TRACEFN;
    enqueueMarked(mCurrentFP);
    EMIT(marked(mCurrentFP));
    mCurrentFP.clear();
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


