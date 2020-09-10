#include "QQSize.h"

QQSize::QQSize() {;}
QQSize::QQSize(const QSize other) : QSize(other) {;}
QQSize::QQSize(const int width, const int height, const int truncate)
    : QSize(width & ~truncate, height & ~truncate) {;}

qreal QQSize::aspect() const
{
    return qreal(width()) / qreal(height());
}

int QQSize::minDimension() const
{
    return qMin(width(), height());
}

int QQSize::area() const
{
    return width() * height();
}

void QQSize::setWidth(int width, qreal aspect)
{
    QSize::setWidth(width);
    QSize::setHeight(width * aspect);
}
