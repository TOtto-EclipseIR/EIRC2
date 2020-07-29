#pragma once

#include <QObject>
#include "BaseMarkerBehavior.h"

class PreScanRectMarkerBehavior : public BaseMarkerBehavior
{
    Q_OBJECT
public:
    PreScanRectMarkerBehavior(MarkerManager *manager);
};

