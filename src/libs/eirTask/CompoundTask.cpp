#include "CompoundTask.h"

#include <eirXfr/Debug.h>

CompoundTask::CompoundTask(const Id &taskId,
                           AbstractTask *parent)
    : AbstractTask(taskId, parent)
{
    TRACEQFI << QOBJNAME(parent) << taskId.name()();
    setObjectName("RootTask:"+taskId.name());
    setParent(parent);

}
