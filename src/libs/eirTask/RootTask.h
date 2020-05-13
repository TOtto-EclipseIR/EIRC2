// file: {repo: EIRC2}./src/libs/eirTask/RootTask.h
#pragma once

#include <QObject>

#include <AbstractTask.h>

class RootTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit RootTask(QObject *parent = nullptr);

signals:

};

