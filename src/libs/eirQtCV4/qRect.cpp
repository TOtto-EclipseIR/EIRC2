#include "qRect.h"

qRect::qRect() {;}

qRect::qRect(const cv::Rect &cvrc)
{
    set(cvrc);
}

void qRect::set(const cv::Rect &cvrc)
{
    setHeight(cvrc.height), setWidth(cvrc.width);
}
