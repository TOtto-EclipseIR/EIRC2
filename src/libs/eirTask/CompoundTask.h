#pragma once

#include <QObject>
#include "AbstractTask.h"

class CompoundTask : public AbstractTask
{
    Q_OBJECT
public:
    CompoundTask(const Id &taskId,
                 AbstractTask *parent = nullptr);
};

