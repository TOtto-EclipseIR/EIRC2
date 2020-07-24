#pragma once
#include "eirObj.h"

#include <QObject>

#include <QList>
#include <QVariant>

#include <eirXfr/Debug.h>
#include <eirType/DualMap.h>
#include <eirType/Id.h>

class EIROBJ_EXPORT ListObject : public QObject
{
    Q_OBJECT
public:
    explicit ListObject(QObject *parent = nullptr);



public:

public slots:
    void clear();
    void dequeue();
    void peek();
    void validate();
    void enqueue(const QVariant &value);

signals:

private:
//?     QList<Uid> mUidList;
    DualMap<Uid, Id> mUidIdDMap;
    DualMap<Uid, QVariant> mUidDMap;
};

