#pragma once

#include <QObject>
#include "AbstractTask.h"

class AtomicTask : public AbstractTask
{
    Q_OBJECT
public:
    AtomicTask(const Id &taskId,
               AbstractTask * parent);
};

