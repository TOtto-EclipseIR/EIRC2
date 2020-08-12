//! @file {EIRC2 repo}./src/libs/eirMarker/AbstractMarkerInterface.h
#pragma once
#include "eirMarker.h"

#include <eirType/MultiName.h>

class EIRMARKER_EXPORT AbstractMarkerInterface // pure virtual
{
public:
    AbstractMarkerInterface();
    virtual MultiName name() const = 0;
};

