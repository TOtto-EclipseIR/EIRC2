#include "cvSize.h"

cvSize::cvSize(const QSize qsize)
{
    width = qsize.width(),
    height = qsize.height();
}
