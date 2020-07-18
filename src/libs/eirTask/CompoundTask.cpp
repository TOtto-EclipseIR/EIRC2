#include "CompoundTask.h"

#include <eirBase/Debug.h>

CompoundTask::CompoundTask(const Id &taskId,
                           AbstractTask *parent)
    : AbstractTask(taskId, parent)
{
    TRACEQFI << QOBJNAME(parent) << taskId.name()();
    setObjectName("RootTask:"+taskId.name());
    setParent(parent);

}
