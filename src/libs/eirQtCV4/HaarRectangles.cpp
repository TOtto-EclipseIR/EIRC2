// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.cpp
#include "HaarRectangles.h"

HaarRectangles::HaarRectangles() {;}

void HaarRectangles::append(const QQRect rect)
{
    mRects.insert(rect.area(), rect);
}

void HaarRectangles::append(const QQRect::List rects)
{
    foreach (QQRect rc, rects) append(rc);
}

void HaarRectangles::operator <<(const QQRect rect)
{
    append(rect);
}

void HaarRectangles::operator <<(const QQRect::List rects)
{
    append(rects);
}

