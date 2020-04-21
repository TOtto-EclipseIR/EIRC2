#include "SessionManager.h"

#include <eirBase/Debug.h>

SessionManager::SessionManager(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    TRACEQOB(parent)
            setObjectName("SessionManager");
}

Uid SessionManager::registerResource(const MultiName &name,
                        AbstractResource *resource)
{
    Uid uid = Uid::create();
    MUSTDO()
    mUidResourceMap.insert(uid, resource);
    mResourceNameMap.insert(uid, name);
    return uid;
}

Uid SessionManager::resourceId(const MultiName &name)
{
    return mResourceNameMap.uid(name);
}
