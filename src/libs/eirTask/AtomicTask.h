#pragma once
// file: {repo: EIRC2}./src/libs/eirTask/AbstractTask.h
#pragma once
#include "eirTask.h"


#include <QObject>
#include "AbstractTask.h"

class EIRTASK_EXPORT AtomicTask : public AbstractTask
{
    Q_OBJECT
public:
    AtomicTask(const Id &taskId,
               AbstractTask * parent);
};

