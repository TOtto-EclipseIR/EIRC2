//! \file ImageReaderQueue.h

#pragma once

#include "BaseImageQueue.h"

class ImageReaderQueue : public BaseImageQueue
{
public:
    ImageReaderQueue(ImageQueueObject *imageQueueObject=nullptr);
    QString peekFirstFileName() const;
    QImage peekFirstImage() const;
    QString dequeueFileName();
    void dequeueVoid();
    QImage takeImage(const QFileInfo &fileInfo);

protected:
    void enqueue(const int recurseDepth=0);
};

