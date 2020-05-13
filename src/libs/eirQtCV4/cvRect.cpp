// file: {EIRC2 repo}./src/libs/eirQtCV/cvRect.cpp
#include "cvRect.h"

cvRect::cvRect() {;}

cvRect::cvRect(const cv::Rect &cvrc) : cv::Rect(cvrc) {;}

void cvRect::set(const QQRect &qqrc)
{
    cv::Rect cvrc(qqrc.x(), qqrc.y(), qqrc.width(), qqrc.height());
    *this = cvrc;
}

QQRect cvRect::qRect() const
{
    return QQRect(x, y, width, height);
}

cvRect::operator QQRect() const
{
    return qRect();
}
