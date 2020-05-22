#include "BaseImageQueue.h"

#include <eirBase/Debug.h>

BaseImageQueue::BaseImageQueue(const QFileInfo &fileInfo,
                        ImageQueueObject *imageQueueObject)
    : cmFileInfo(fileInfo)
    , mpQueueObject(imageQueueObject)
{
    TRACEFN
}

ImageQueueObject *BaseImageQueue::queueObject()
{
    return mpQueueObject;
}
