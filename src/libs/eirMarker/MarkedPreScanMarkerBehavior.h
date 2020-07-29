#pragma once

#include <QObject>
#include "BaseMarkerBehavior.h"

class MarkedPreScanMarkerBehavior : public BaseMarkerBehavior
{
    Q_OBJECT
public:
    MarkedPreScanMarkerBehavior(MarkerManager *manager);
};

