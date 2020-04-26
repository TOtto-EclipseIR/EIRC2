// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.cpp
#include "HaarRectangles.h"

HaarRectangles::HaarRectangles() {;}

void HaarRectangles::append(const QQRect rect)
{
    mRects.insert(rect.area(), rect);
}

void HaarRectangles::append(const QQRectList rects)
{
    foreach (QQRect rc, rects) append(rc);
}

void HaarRectangles::operator <<(const QQRect rect)
{
    append(rect);
}

void HaarRectangles::operator <<(const QQRectList rects)
{
    append(rects);
}

