#include "BaseMarkerBehavior.h"

#include <eirType/BasicName.h>
#include <eirXfr/Debug.h>

#include "BaseMarker.h"

BaseMarkerBehavior::
    BaseMarkerBehavior(MarkerManager *manager)
    : cmpMarker(manager)
{
    TRACEQFI << QOBJNAME(manager) << manager->name()();
}

BasicName BaseMarkerBehavior::name() const
{
    return cmpMarker->name();
}
