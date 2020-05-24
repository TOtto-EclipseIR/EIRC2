//! \file ImageWriterQueue.h

#pragma once

#include "BaseImageQueue.h"

class ImageWriterQueue : public BaseImageQueue
{
public:
    ImageWriterQueue(ImageQueueObject *imageQueueObject=nullptr);
    void enqueue(const QString &fileName,
                 const QImage &image);

};

