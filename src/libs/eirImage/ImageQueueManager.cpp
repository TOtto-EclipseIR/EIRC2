//! \file ImageQueueManager.cpp

#include "ImageQueueManager.h"

#include <eirBase/Debug.h>

ImageQueueManager::ImageQueueManager(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("ImageQueueManager");
}

ImageWriterQueue *ImageQueueManager::newWriterQueue(
        const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    MUSTDO(it)
    return nullptr;
}

ImageReaderQueue *ImageQueueManager::newReaderQueue(
        const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    MUSTDO(it)
    return nullptr;
}

ImageDirectoryQueue *ImageQueueManager::newDirectoryQueue(
        const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    MUSTDO(it)
    return nullptr;
}
