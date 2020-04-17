#include "QQRect.h"

QQRect::QQRect() {;}

QQRect::QQRect(int x, int y, int width, int height)
    : QRect(x, y, width, height) {;}

QQRect::QQRect(const QSize size, const QPoint center)
    : QRect(QPoint(center.x() - size.width()  / 2,
                   center.y() - size.height() / 2), size) {;}

