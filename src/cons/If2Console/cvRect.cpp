#include "cvRect.h"

cvRect::cvRect() {;}

QRect cvRect::toQRect() const
{
    return QRect(mCvRect.x,     mCvRect.y,
                 mCvRect.width, mCvRect.height);
}

cvRect::operator QRect() const
{
    return toQRect();
}
