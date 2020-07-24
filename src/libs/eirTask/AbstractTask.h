// file: {repo: EIRC2}./src/libs/eirTask/AbstractTask.h
#pragma once
#include "eirTask.h"

#include <QObject>

#include <QList>

#include <eirType/Id.h>

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
    AbstractTask(const Id &taskId,
                          AbstractTask *parentTask = nullptr);
    ~AbstractTask();
    Id id() const;
    MultiName name() const;

public:
    virtual bool run() = 0;

    //----- Property getters -----
    bool isActive() const;
    AbstractTask *  parentTask() const;
    AbstractTask *  previousTask() const;
    AbstractTask *  nextTask() const;
    List childTaskList() const;

protected:
    virtual void entryEvent(QEvent *event) = 0;
    virtual void exitEvent(QEvent *event) = 0;
    bool event(QEvent *event) override;

private slots:
    //----- Property setters -----
    void setActive(bool set=true);
    void setParentTask(AbstractTask * task);
    void setPrevoiusTask(AbstractTask * task);
    void setNextTask(AbstractTask * task);


signals:
    void entered(QPrivateSignal);
    void exited(QPrivateSignal);
    //----- Property notifiers -----
    void activeChanged(bool isActive);
    void parentTaskChanged(AbstractTask * task);
    void previousTaskChanged(AbstractTask * task);
    void nextTaskChanged(AbstractTask * task);
    void childTaskListChanged(List childTasks);
    void prerequsiteTaskListChanged(List prerequsiteTasks);

private:
    const Id cmId;
    //----- Property values -----
    bool mActive=false;
    AbstractTask *  mpParentTask=nullptr;
    AbstractTask *  mpPreviousTask=nullptr;
    AbstractTask *  mpNextTask=nullptr;
    List mChildTaskList;
    List mPrerequsiteTaskList;
};


