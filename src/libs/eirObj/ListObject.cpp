#include "ListObject.h"

#include <eirXfr/Debug.h>

ListObject::ListObject(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << QOBJNAME(parent);
    setObjectName("ListObject");
}

void ListObject::clear()
{
    TRACEFN;
    mUidIdDMap.clear();
    mUidDMap.clear();
}

void ListObject::dequeue()
{

}

void ListObject::peek()
{

}

void ListObject::validate()
{

}

void ListObject::enqueue(const QVariant &value)
{

}

