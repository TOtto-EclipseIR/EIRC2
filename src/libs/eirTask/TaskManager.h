// file: {repo: EIRC2}./src/libs/eirTask/TaskManager.h
#pragma once
#include "eirTask.h"


#include <QObject>

class EIRTASK_EXPORT TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);

signals:

};

