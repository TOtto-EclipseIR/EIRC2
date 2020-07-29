#include "BaseMarker.h"

#include <eirXfr/Debug.h>


#include "MarkerManager.h"

BaseMarker::BaseMarker(BaseMarkerBehavior *behavior,
                       MarkerManager *manager,
                       const BasicName &markedName,
                       const QDir &dir,
                       const Configuration &markerConfig)
    : QObject(manager)
    , cmpManager(manager)
    , cmMarkerName(markedName)
    , cmpBehavoir(behavior)
    , cmDir(dir)
    , mMarkerConfig(markerConfig)
{
    TRACEQFI << QOBJNAME(cmpManager) << cmMarkerName() << cmDir;
    mMarkerConfig.dump();
}

QDir BaseMarker::dir() const
{
    return cmDir;
}


