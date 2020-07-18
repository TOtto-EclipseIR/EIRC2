// file: {repo: EIRC2}./src/libs/eirTask/RootTask.cpp
#include "RootTask.h"

#include <eirBase/Debug.h>

RootTask::RootTask(const Id &taskId, QObject *parent)
    : AbstractTask(taskId, nullptr)
{
    TRACEQFI << QOBJNAME(parent) << taskId.name()();
    setObjectName("RootTask:"+taskId.name());
    setParent(parent);

    // RootTask should not have a parent Task
    AbstractTask * parentTask = qobject_cast<AbstractTask *>(parent);
    BEXPECTNE(nullptr, parentTask);
}
