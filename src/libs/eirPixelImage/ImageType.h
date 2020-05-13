#include "eirPixelImage.h"
#pragma once

#include <eirType/Enumeration.h>

#define IMAGETYPE_ENUM(NV) \
    NV(Null, = 0)  \
    NV(Miscellaneous,)   \

class EIRPIXELIMAGE_EXPORT ImageType : public Enumeration
{
    DECLARE_ENUMERATION(ImageType, IMAGETYPE_ENUM)
};
