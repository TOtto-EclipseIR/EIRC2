#include "AtomicTask.h"

#include <eirXfr/Debug.h>

AtomicTask::AtomicTask(const Id &taskId,
                       AbstractTask *parent)
    : AbstractTask(taskId, parent)
{
    TRACEQFI << QOBJNAME(parent) << taskId();
    setObjectName("AtomicTask:"+taskId.toString());
}
