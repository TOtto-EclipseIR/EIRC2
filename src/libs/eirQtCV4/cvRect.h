// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.h
#pragma once
#include "eirQtCV4.h"

#ifndef STUB_OPENCV4
#include <opencv2/core.hpp>
#endif

#include <eirType/QQRect.h>

class EIRQTCV4_EXPORT cvRect : public QQRect
{
public:
    cvRect();
#ifndef STUB_OPENCV4
    cvRect(const cvRect &cvrc);
    void set(const cvRect &cvrc);
#endif
};

