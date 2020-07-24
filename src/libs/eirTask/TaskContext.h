// file: {repo: EIRC2}./src/libs/eirTask/TaskContext.h
#pragma once
#include "eirTask.h"


#include <eirType/Id.h>

class EIRTASK_EXPORT TaskContext
{
public:
    TaskContext(const Id &contextId);

private:
    Id cmContextId;
};

