#include "QQSize.h"

QQSize::QQSize() {;}
QQSize::QQSize(const QSize other) : QSize(other) {;}
QQSize::QQSize(const int width, const int height, const int truncate)
    : QSize(width & ~truncate, height & ~truncate) {;}

int QQSize::area() const
{
    return width() * height();
}
