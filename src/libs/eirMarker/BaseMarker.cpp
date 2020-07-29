#include "BaseMarker.h"

#include <eirXfr/Debug.h>


#include "MarkerManager.h"

BaseMarker::BaseMarker(MarkerManager *manager,
                       BaseMarkerBehavior *behavior,
                       const BasicName &markedName,
                       const QDir &dir,
                       const Configuration &markerConfig)
    : QObject(manager)
    , cmpManager(manager)
    , cmMarkedName(markedName)
    , cmpBehavoir(behavior)
    , cmDir(dir)
    , mMarkerConfig(markerConfig)
{
    TRACEQFI << QOBJNAME(cmpManager) << cmMarkedName() << cmDir;
    mMarkerConfig.dump();
}

QDir BaseMarker::dir() const
{
    return cmDir;
}


