#include "ObjectDetector.h"

#include <QTimer>

#include <eirXfr/Debug.h>

QHash<cvCascadeType, ObjectDetector::This> ObjectDetector::smTypeDetectorHash;

ObjectDetector::ObjectDetector(const cvCascade::Type type,
                               ConfigObject *cfgObj,
                               QObject *parent)
    : QObject(parent)
//    , cmType(type)
    , mCascade(type)
    , cmpConfig(cfgObj)
    , cmpTimer(new QTimer(parent))
{
    TRACEQFI << cvCascade::typeName(type)() << QOBJNAME(parent);
    setObjectName("ObjectDetector");
    TSTALLOC(cmpConfig);
    TSTALLOC(cmpTimer);
    cmpConfig->setObjectName("ConfigObject:ObjectDetector");
    cmpTimer->setObjectName("QTimer:ObjectDetector");
    if (smTypeDetectorHash.contains(type))
    {
        ObjectDetector * oldOD = smTypeDetectorHash.value(type);
        oldOD->deleteLater();
        smTypeDetectorHash.remove(type);
    }
    smTypeDetectorHash.insert(type, this);
    EMIT(ctored());
    //QTimer::singleShot(100, this, &ObjectDetector::initialize);
}

ObjectDetector::~ObjectDetector()
{
    cvCascadeType type = cascade()->type();
    if (smTypeDetectorHash.contains(type)
            && smTypeDetectorHash.value(type) == this)
        smTypeDetectorHash.remove(type);
}

ObjectDetector *ObjectDetector::p(const cvCascadeType type)
{
    return smTypeDetectorHash[type];
}

cvCascade *ObjectDetector::cascade()
{
    return &mCascade;
}

ObjDetPak &ObjectDetector::pak(const Uuid uuid)
{
    return mPakMap[uuid];
}

QQRectList ObjectDetector::process(const QFileInfo &inputFileInfo
                                   , bool showDetect)
{
    TRACEQFI << inputFileInfo;
    ObjDetPak pak(inputFileInfo, true);
    QQImage inputImage = pak.inputImage();
    mProcessInputImage = inputImage;
    cascade()->detectRectangles(Configuration(), inputImage, showDetect);
    QQRectList rectList = cascade()->rectList();
    rectList = groupByUnion(rectList);
    return rectList;
}

QQRectList ObjectDetector::groupByUnion(const QQRectList &inputRects)
{
    TRACEQFI << inputRects;
    QQRectList resultRects;
    QQRectList remainingRects = inputRects;
    while ( ! remainingRects.isEmpty())
    {
        QQRect currentRect = remainingRects.takeFirst();
        QQRectList nextRects;
        {
            while ( ! remainingRects.isEmpty())
            {
                QQRect thisRect = remainingRects.takeFirst();
                if (currentRect.overlap(thisRect) > 0.1)
                    currentRect = QQRect(currentRect.united(thisRect));
                else
                    nextRects << thisRect;
            }
        }
        resultRects << currentRect;
        remainingRects = nextRects;
    }
    TRACE << resultRects;
    return resultRects;
}

QQImage ObjectDetector::processInputImage() const
{
    return mProcessInputImage;
}

void ObjectDetector::start()
{
    Milliseconds pulseMsec = mObjDetConfig.signedInt("PulseMsec");
    TRACEQFI << pulseMsec;
    EXPECT(pulseMsec);
    if (pulseMsec > 0)
    {
        CONNECT(cmpTimer, &QTimer::timeout,
                this, &ObjectDetector::pulse);
        cmpTimer->start(pulseMsec);
        EMIT(started());
    }
    else
    {
        ERROR << "Timer not start()ed";
    }
}

void ObjectDetector::enqueue(const QFileInfo &inputFileInfo)
{
    bool autoLoad = mObjDetConfig.boolean("InputQueue/AutoLoad");
    TRACEQFI << inputFileInfo << autoLoad;
    ObjDetPak pak(inputFileInfo, autoLoad);
    Uuid uuid = pak.uuid();
    DUMPVAL(uuid);
    mPakMap.insert(uuid, pak);
    EMIT(pakInserted(mPakMap.size()));
    if ( ! autoLoad)
    {
        mInputQueue.enqueue(uuid);
        EMIT(inputQueued(uuid));
        EMIT(inputQueued(mInputQueue.size()));
        EMIT(inputQueueNotEmpty());
    }
}

void ObjectDetector::dequeue(const int count)
{
    TRACEQFI << count;
    MUSTDO(it);

}

void ObjectDetector::release(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);

}

void ObjectDetector::stop()
{
    TRACEFN;
    DISCONNECT(cmpTimer, &QTimer::timeout,
               this, &ObjectDetector::pulse);
    EMIT(stopped());
}

void ObjectDetector::initialize()
{
    TRACEFN;
    NEEDDO(anyConnect);
    EMIT(initialized());
    QTimer::singleShot(100, this, &ObjectDetector::setDefaults);
}

void ObjectDetector::setDefaults()
{
    TRACEFN;
    mObjDetConfig.setDefault("PulseMsec", 64);
    mObjDetConfig.setDefault("ProcessedHoldCount", 32);
    mObjDetConfig.setDefault("ReleasedRemoveCount", 32);
    mObjDetConfig.setDefault("InputQueue/AutoLoad", false);
    TODO(RectFinder/TBD);
    TODO(RectGrouper/TBD);
    EMIT(defaultsSet());
    QTimer::singleShot(100, this, &ObjectDetector::configure);
}

void ObjectDetector::configure()
{
    TRACEFN;
    mObjDetConfig += cmpConfig->configuration().
            extract(cascade()->typeName()+"/ObjectDetector");
    LATERDO("connectDispatcher");
    EMIT(configured());
    QTimer::singleShot(100, this, &ObjectDetector::readyStart);
}

void ObjectDetector::readyStart()
{
    TRACEFN;
    TODO(anything);
    EMIT(ready());
    //QTimer::singleShot(100, this, &ObjectDetector::nextslot);
}

void ObjectDetector::pulse()
{
    TRACEFN;
    static int kHold = 0;
    int nPak        = mPakMap.size();
    int nInput      = mInputQueue.size();
    int nFinder     = mFinderQueue.size();
    int nGrouper    = mGrouperQueue.size();
    int nProcessed  = mProcessedQueue.size();
    int nReleased   = mReleasedQueue.size();

    int processedLimit  = mObjDetConfig.unsignedInt("ProcessedHoldCount");
    int holdLimit       = mObjDetConfig.unsignedInt("HoldMaxIntervals", 4);
    int releasedLimit   = mObjDetConfig.unsignedInt("ReleasedRemoveCount");
    DUMP << "Pulse:" << nPak
         << nInput << nFinder << nGrouper << nProcessed << nReleased
         << processedLimit << holdLimit << releasedLimit;
    LATERDO(PerformanceRecorder);
    NEEDDO(RefactorReturns&TrackTime);
    // should we wait for client to process more?
    if (nProcessed > processedLimit)
        if (++kHold < holdLimit)
            return;                                         /*/=======\*/
    kHold = 0;

    // should we make room in the KitMap?
    if (nReleased > releasedLimit
            || (0 == nInput + nGrouper + nFinder))
    {
        while ( ! mReleasedQueue.isEmpty())
        {
            Uuid removeUuid = mReleasedQueue.dequeue();
            removeReleased(removeUuid);
        }
        return;                                             /*/=======\*/
    }

    if (nFinder >= nGrouper && nFinder >= nInput && nFinder > 0)
    {
        findRects(mFinderQueue.dequeue());
    }
    else if (nInput >= nGrouper && nInput >= nFinder && nInput > 0)
    {
        TRACE << "loadInput()" << mInputQueue.head().trace();
        loadInput(mInputQueue.dequeue());
    }
    else if (nGrouper >= nInput && nGrouper >= nFinder && nGrouper > 0)
    {
        groupRects(mGrouperQueue.dequeue());
    }
    else
    {
        ; // nothing to do, wait for next time?
    }
}

void ObjectDetector::loadInput(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    pak(uuid).loadInputImage();
    if ( ! pak(uuid).inputImage().isNull())
        mFinderQueue.enqueue(uuid);
    else
        ERROR << "inputImage() null" << uuid.trace();
    TRACERTV();
}

void ObjectDetector::findRects(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    QQImage inputImage = pak(uuid).inputImage();
    if (inputImage.isNull())
    {
        ERROR << "inputImage() null" << uuid.trace();
    }
    else
    {
        int rects = cascade()->detectRectangles(Configuration(), inputImage);
        if (rects < 0)
            ERROR << "detectRectangles() Error:" << rects;
        else if (0 == rects)
            WARN << "No Rectangles Detected";
        else
            TRACE << rects << "Detectected";
    }
    MUSTDO(saveRectsAndEnqueueGrouper);
}

void ObjectDetector::groupRects(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);


}

void ObjectDetector::removeReleased(const Uuid uuid)
{
    TRACEQFI << uuid.trace();
    MUSTDO(it);


}
