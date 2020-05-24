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

void BaseImageQueue::setOutputDir(const QDir &dir)
{
    TRACEQFI << dir;
    mOutputDir = dir;

}
/*
void BaseImageQueue::enqueue(const QString &fileName,
                             const QImage &image)
{
    TRACEQFI << fileName << image;
}
*/
QQueue<QString> BaseImageQueue::fileInfoQueue() const
{
    return mFileNameQueue;
}

void BaseImageQueue::setFileInfoQueue(const QQueue<QString> &fileInfoQueue)
{
    mFileNameQueue = fileInfoQueue;
}
