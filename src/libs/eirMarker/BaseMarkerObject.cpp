#include "BaseMarkerObject.h"

#include <eirXfr/Debug.h>

BaseMarkerObject::BaseMarkerObject(AbstractMarkerInterface *behavior,
                                   QObject *parent)
    : QObject(parent)
    , cmpBehavior(behavior)
{
    TRACEFN;
    setObjectName("BaseMarkerPlugin");
}

MultiName BaseMarkerObject::markerName() const
{
    return cmpBehavior->name();
}

AbstractMarkerInterface *BaseMarkerObject::behavior() const
{
    return cmpBehavior;
}
