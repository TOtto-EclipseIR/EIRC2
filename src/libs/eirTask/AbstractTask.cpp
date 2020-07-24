// file: {repo: EIRC2}./src/libs/eirTask/AbstractTask.cpp
#include "AbstractTask.h"

#include <eirXfr/Debug.h>

AbstractTask::AbstractTask(const Id &taskId,

                           AbstractTask *parentTask)
    : QObject(parentTask)
    , cmId(taskId)
{
    TRACEQFI << taskId() << QOBJNAME(parentTask);
    TRACE << taskId.uuid().toString();
    setObjectName("AbstractTask"+taskId.toString());
    setParentTask(parentTask);
}

AbstractTask::~AbstractTask()
{

}

Id AbstractTask::id() const
{
    return cmId;
}

MultiName AbstractTask::name() const
{
    return cmId.name();
}

bool AbstractTask::isActive() const
{
    return mActive;
}

AbstractTask *AbstractTask::parentTask() const
{
    return mpParentTask;
}

AbstractTask *AbstractTask::previousTask() const
{
    return mpPreviousTask;
}

AbstractTask *AbstractTask::nextTask() const
{
    return mpNextTask;
}

AbstractTask::List AbstractTask::childTaskList() const
{
    return mChildTaskList;
}

bool AbstractTask::event(QEvent *event)
{
    return QObject::event(event);
}

void AbstractTask::setActive(bool set)
{
    mActive = set;
}

void AbstractTask::setParentTask(AbstractTask *task)
{
    mpParentTask = task;
}

void AbstractTask::setPrevoiusTask(AbstractTask *task)
{
    mpPreviousTask = task;
}

void AbstractTask::setNextTask(AbstractTask *task)
{
    mpNextTask = task;
}
