// file: {repo: EIRC2}./src/libs/eirTask/CompoundTask.h
#pragma once
#include "eirTask.h"


#include <QObject>
#include "AbstractTask.h"

class EIRTASK_EXPORT CompoundTask : public AbstractTask
{
    Q_OBJECT
public:
    CompoundTask(const Id &taskId,
                 AbstractTask *parent = nullptr);
};

