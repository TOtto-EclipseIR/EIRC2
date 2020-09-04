#include "ObjectDetector.h"

#include <QTimer>

#include <eirXfr/Debug.h>

ObjectDetector::ObjectDetector(const cvCascade::Type type,
                               ConfigObject *cfgObj,
                               QObject *parent)
    : QObject(parent)
    , cmType(type)
    , mCascade(cmType)
    , cmpConfig(cfgObj)
    , cmpTimer(new QTimer(parent))
{
    TRACEQFI << cvCascade::typeName(type)() << QOBJNAME(parent);
    setObjectName("ObjectDetector");
    TSTALLOC(cmpConfig);
    TSTALLOC(cmpTimer);
    cmpConfig->setObjectName("ConfigObject:ObjectDetector");
    cmpTimer->setObjectName("QTimer:ObjectDetector");
    EMIT(ctored());
    QTimer::singleShot(100, this, &ObjectDetector::initialize);
}

cvCascade *ObjectDetector::cascade()
{
    return &mCascade;
}

void ObjectDetector::start(const Milliseconds pulseMsec)
{
    TRACEQFI << pulseMsec;
    MUSTDO(it);

    EMIT(started());
}

void ObjectDetector::enqueue(const QFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    ObjDetPak pak(inputFileInfo, false);
    Uuid uuid = pak.uuid();
    mPakMap.insert(uuid, pak);
    EMIT(pakInserted(mPakMap.size()));
    mInputQueue.enqueue(uuid);
    EMIT(inputQueued(uuid));
    EMIT(inputQueued(mInputQueue.size()));
    EMIT(inputQueueNotEmpty());
}

void ObjectDetector::dequeue(const int count)
{
    TRACEQFI << count;
    MUSTDO(it);

}

void ObjectDetector::release(const Uuid uuid)
{
    TRACEQFI << uuid.tail();
    MUSTDO(it);

}

void ObjectDetector::stop()
{
    TRACEFN;
    MUSTDO(StopTimer);

    EMIT(stopped());
}

void ObjectDetector::initialize()
{
    TRACEFN;
    MUSTDO(it);

    EMIT(initialized());
    QTimer::singleShot(100, this, &ObjectDetector::configure);
}

void ObjectDetector::configure()
{
    TRACEFN;
    MUSTDO(it);

    EMIT(configured());
    QTimer::singleShot(100, this, &ObjectDetector::readyStart);
}

void ObjectDetector::readyStart()
{
    TRACEFN;
    MUSTDO(it);

    EMIT(ready());
    //QTimer::singleShot(100, this, &ObjectDetector::initialize);
}

void ObjectDetector::pulse()
{
    TRACEFN;
    MUSTDO(it);

}

void ObjectDetector::loadInput(const Uuid uuid)
{
    TRACEQFI << uuid.tail();
    MUSTDO(it);


}

void ObjectDetector::findRects(const Uuid uuid)
{
    TRACEQFI << uuid.tail();
    MUSTDO(it);


}

void ObjectDetector::groupRects(const Uuid uuid)
{
    TRACEQFI << uuid.tail();
    MUSTDO(it);


}

void ObjectDetector::removeReleased(const Uuid uuid)
{
    TRACEQFI << uuid.tail();
    MUSTDO(it);


}
