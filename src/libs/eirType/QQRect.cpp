// file: {EIRC2 repo)./src/libs/eirType/QQRect.cpp
#include "QQRect.h"

QQRect::QQRect() {;}

QQRect::QQRect(int x, int y, int width, int height)
    : QRect(x, y, width, height) {;}

QQRect::QQRect(const QSize size, const QPoint center)
    : QRect(center.x() - size.width()  / 2,
            center.y() - size.height() / 2,
            size.height(), size.width()) {;}

QQRect::QQRect(const QRectF rcf) { set(rcf); }

QQRect QQRect::set(const QRectF rcf)
{
    QQRect rc(qRound(rcf.x()), qRound(rcf.y()),
              qRound(rcf.width()), qRound(rcf.width()));
    return rc;
}

void QQRect::set(const QSize size, const QPoint center)
{
    setRect(center.x() - size.width()  / 2,
            center.y() - size.height() / 2,
            size.height(), size.width());
}

int QQRect::area() const
{
    return height() * width();
}

