#include "TaskContext.h"

#include <eirXfr/Debug.h>

TaskContext::TaskContext(const Id &contextId)
    : cmContextId(contextId)
{
    TRACEQFI << contextId.name()();

}
