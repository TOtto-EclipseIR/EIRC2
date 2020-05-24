//! \file ImageQueueManager.cpp

#include "ImageQueueManager.h"

#include <eirBase/Debug.h>

ImageQueueManager::ImageQueueManager(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("ImageQueueManager");
}

ImageWriterQueue *ImageQueueManager::newWriterQueue(const BasicName &name,

        const QDir &dir)
{
    TRACEQFI << dir;
    MUSTDO(it)
    return nullptr;
}

ImageReaderQueue *ImageQueueManager::newReaderQueue(const BasicName &name,

        const QDir &dir)
{
    TRACEQFI << dir;
    MUSTDO(it)
    return nullptr;
}

ImageDirectoryQueue *ImageQueueManager::newDirectoryQueue(const BasicName &name,

        const QDir &dir)
{
    TRACEQFI << dir;
    MUSTDO(it)
    return nullptr;
}
