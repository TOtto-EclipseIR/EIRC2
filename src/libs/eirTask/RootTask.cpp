// file: {repo: EIRC2}./src/libs/eirTask/RootTask.cpp
#include "RootTask.h"

#include <eirBase/Debug.h>

RootTask::RootTask(QObject *parent)
    : AbstractTask(nullptr)
{
    TRACEQFI << QOBJNAME(parent);
    setObjectName("RootTask");
    setParent(parent);

    // RootTask should not have a parent Task
    AbstractTask * parentTask = qobject_cast<AbstractTask *>(parent);
    BEXPECTNE(nullptr, parentTask);
}
