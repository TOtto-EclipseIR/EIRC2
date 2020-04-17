#include "AbstractResource.h"

#include <eirBase/Debug.h>

AbstractResource::AbstractResource(const Class resourceClass,
                                   const MultiName &name,
                                   QObject *parent)
    : SessionManager(parent)
    , cmResourceClass(resourceClass)
    , cmResourceId(resourceId(name))
    , cmResourceName(name)
{
    TRACEFN
    TRACEQOB(parent);
    setObjectName("AbstractResource");
}

AbstractResource::Class AbstractResource::resourceClass() const
{
    return cmResourceClass;
}
