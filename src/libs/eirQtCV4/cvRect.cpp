#include "cvRect.h"

cvRect::cvRect() {;}

#ifndef STUB_OPENCV4
cvRect::cvRect(const cvRect &cvrc)
    : QQRect(cvrc.size(), cvrc.center()) {;}

void cvRect::set(const cvRect &cvrc)
{
    setX(cvrc.x()), setY(cvrc.y()),
         setWidth(width()), setHeight(height());
}
#endif
