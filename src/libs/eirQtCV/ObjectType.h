#pragma once
#include "eirQtCV.h"

#include <eirType/Enumeration.h>
#define OBJECTTYPE_ENUM(NV) \
    NV(null, = 0)  \
    NV(FrontalFace,)   \
    NV(LeftEye,)   \
    NV(RightEye,)   \
    NV(EitherEye,)   \
    NV(BothEyes,)   \

class EIRQTCV_EXPORT ObjectType : public Enumeration
{
    DECLARE_ENUMERATION(ObjectType, OBJECTTYPE_ENUM)
};

