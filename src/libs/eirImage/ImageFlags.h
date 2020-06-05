// file:{EIRC2 repo}./src/libs/eirImage/ImageFlags.h
//! \file ImageFlags.h
#pragma once
#include "eirImage.h"

#pragma once

#include <eirType/BitFlags.h>

class EIRIMAGE_EXPORT ImageFlags : public BitFlags
{
public:
    ImageFlags();

private:
    void ctorOnce();

public:
    const int cmImageOutputFlagsFrameBase       = 64 + cmImageFlagsBase;
    const int cmImageOutputFlagsFaceBase        = 64 + cmImageOutputFlagsFrameBase;
    const int cmImageOutputFlagsBodyBase        = 64 + cmImageOutputFlagsFaceBase;
    // others TBD ...
    const int cmImageFlagsEnd                   = 15 + cmImageOutputFlagsBodyBase;
};

