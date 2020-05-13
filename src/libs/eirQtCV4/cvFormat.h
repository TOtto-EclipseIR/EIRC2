// file; {EIRC2 repo}./src/libs/eirQtCV4/cvFormat.h
#pragma once
#include "eirQtCV4.h"

#include <QImage>

#include <eirType/Enumeration.h>

#define CVFORMAT_ENUM(NV) \
    NV(null, = 0)  \
    NV(size,)   \


class EIRQTCV4_EXPORT cvFormat : public Enumeration
{
    DECLARE_ENUMERATION(cvFormat, CVFORMAT_ENUM)
public:
//    cvFormat();
};

