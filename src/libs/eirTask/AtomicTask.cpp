#include "AtomicTask.h"

#include <eirBase/Debug.h>

AtomicTask::AtomicTask(const Id &taskId,
                       AbstractTask *parent)
    : AbstractTask(taskId, parent)
{
    TRACEQFI << QOBJNAME(parent) << taskId();
    setObjectName("AtomicTask:"+taskId);
}
