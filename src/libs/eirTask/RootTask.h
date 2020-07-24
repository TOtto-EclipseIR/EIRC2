// file: {repo: EIRC2}./src/libs/eirTask/RootTask.h
#pragma once
#include "eirTask.h"

#include <QObject>

#include <AbstractTask.h>

class EIRTASK_EXPORT RootTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit RootTask(const Id &taskId,
                      QObject *parent = nullptr);

signals:

};

