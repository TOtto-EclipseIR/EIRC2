#include "ObjectDetector.h"

#include <eirXfr/Debug.h>

ObjectDetector::ObjectDetector(const cvCascade::Type type, QObject *parent)
    : QObject(parent)
    , cmType(type)
    , mCascade(cmType)
{
    TRACEQFI << cvCascade::typeName(type)() << QOBJNAME(parent);
}

cvCascade *ObjectDetector::cascade()
{
    return &mCascade;
}

void ObjectDetector::enqueue(const QFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    ObjDetPak pak(inputFileInfo);
    mInputQueue.enqueue(pak);
    EMIT(queued(pak));
    EMIT(queued(mInputQueue.size()));
    EMIT(queueNotEmpty());
}
