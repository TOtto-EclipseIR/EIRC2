//! \file ImageFlags.ch

#pragma once

#include <eirType/BitFlags.h>

class ImageFlags : public BitFlags
{
public:
    ImageFlags();

private:
    void ctorOnce();

private:
    const int cmImageFlagsBase          = 1024 + 256;
    const int cmImageFlagsFrameBase     = 16 + cmImageFlagsBase;
    const int cmImageFlagsFaceBase      = 64 + cmImageFlagsFrameBase;
    const int cmImageFlagsBodyBase      = 64 + cmImageFlagsFaceBase;
    const int cmImageFlagsEnd           = 15 + cmImageFlagsBodyBase;
};

