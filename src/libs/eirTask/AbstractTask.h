// file: {repo: EIRC2}./src/libs/eirTask/AbstractTask.h
#pragma once
#include "eirTask.h"

#include <QObject>

#include <QList>


class EIRTASK_EXPORT AbstractTask : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mActive READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(AbstractTask * mpParentTask READ parentTask WRITE setParentTask NOTIFY parentTaskChanged)
    Q_PROPERTY(AbstractTask * mpPreviousTask READ previousTask WRITE setPrevoiusTask NOTIFY previousTaskChanged)
    Q_PROPERTY(AbstractTask * mpNextTask READ nextTask WRITE setNextTask NOTIFY nextTaskChanged)
    Q_PROPERTY(List mChildTaskList READ childTaskList NOTIFY childTaskListChanged)

public:
    typedef QList<AbstractTask *> List;

public:
    explicit AbstractTask(AbstractTask *parent = nullptr);
    //----- Property getters -----
    bool isActive() const;
    AbstractTask *  parentTask() const;
    AbstractTask *  previousTask() const;
    AbstractTask *  nextTask() const;
    List childTaskList() const;

private slots:
    //----- Property setters -----
    void setActive(bool set);
    void setParentTask(AbstractTask * task);
    void setPrevoiusTask(AbstractTask * task);
    void setNextTask(AbstractTask * task);


signals:
    //----- Property notifiers -----
    void activeChanged(bool is);
    void parentTaskChanged(AbstractTask * task);
    void previousTaskChanged(AbstractTask * task);
    void nextTaskChanged(AbstractTask * task);
    void childTaskListChanged(List childTasks);

private:
    //----- Property values -----
    bool mActive=false;
    AbstractTask *  mpParentTask=nullptr;
    AbstractTask *  mpPreviousTask=nullptr;
    AbstractTask *  mpNextTask=nullptr;
    List mChildTaskList;
};















































