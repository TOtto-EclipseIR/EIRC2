#pragma once

#include <eirBase/Id.h>

class TaskContext
{
public:
    TaskContext(const Id &contextId);

private:
    Id cmContextId;
};

