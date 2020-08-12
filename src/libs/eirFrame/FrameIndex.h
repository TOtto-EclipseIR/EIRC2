// file: {repo: EIRC2}./src/libs/eirFrame/FrameIndex.h
#pragma once
#include "eirFrame.h"

#include <eirType/Enumeration.h>

#define FRAMEINDEX_ENUM(NV) \
    NV(nullFrameIndex, = 0)  \
    NV(Raw,)   \
    NV(Detect,)   \
    NV(PreScanRect,)   \
    NV(MarkedPreScan,)   \
    NV(sizeFrameIndex,)   \

class EIRFRAME_EXPORT FrameIndex : public Enumeration
{
    DECLARE_ENUMERATION(FrameIndex, FRAMEINDEX_ENUM)
};

