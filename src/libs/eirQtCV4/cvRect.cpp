// file: {EIRC2 repo}./src/libs/eirQtCV/cvRect.cpp
#include "cvRect.h"

cvRect::cvRect() {;}

cvRect::cvRect(const cv::Rect &cvrc)
{
    set(cvrc);
}

void cvRect::set(const cv::Rect &cvrc)
{
    setX(cvrc.x), setY(cvrc.y),
         setWidth(width()), setHeight(height());
}
