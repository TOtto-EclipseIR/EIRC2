//! \file BaseImageQueue.cpp

#include "BaseImageQueue.h"

#include <eirBase/Debug.h>

#include "ImageQueueObject.h"

BaseImageQueue::BaseImageQueue(ImageQueueObject *imageQueueObject)
    : mpQueueObject(imageQueueObject
                    ? imageQueueObject
                    : new ImageQueueObject())
{
    TRACEFN
}

ImageQueueObject *BaseImageQueue::queueObject()
{
    return mpQueueObject;
}

void BaseImageQueue::setInputDir(const QDir &dir)
{
    TRACEQFI << dir;
    mInputDir = dir;
}
