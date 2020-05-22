#include "ImageFileQueueManager.h"

#include <eirBase/Debug.h>

ImageFileQueueManager::ImageFileQueueManager(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("ImageFileQueueManager");
}
