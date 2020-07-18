#include "TaskContext.h"

#include <eirBase/Debug.h>

TaskContext::TaskContext(const Id &contextId)
    : cmContextId(contextId)
{
    TRACEQFI << contextId.name()();

}
