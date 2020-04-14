// file: {repo: EIRC2}./src/libs/eirTask/RootTask.cpp
#include "RootTask.h"

RootTask::RootTask(QObject *parent)
    : AbstractTask(nullptr)
{
    setParent(parent);
}
