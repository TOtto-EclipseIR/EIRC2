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

    const int cmImageQFormatFlagsBase           =  0 + cmImageFlagsBase;
    const int cmImageUserFormatFlagsBase        = 64 + cmImageFlagsBase;
    const int cmImageOutputFlagsFrameBase       =  0 + cmImageOutputFlagsBase;
    const int cmImageOutputFlagsFaceBase        = 64 + cmImageOutputFlagsFrameBase;
    const int cmImageOutputFlagsBodyBase        = 64 + cmImageOutputFlagsFaceBase;
    const int cmImageOutputFlagsEnd             = 15 + cmImageOutputFlagsBodyBase;

    // others TBD ...
};

