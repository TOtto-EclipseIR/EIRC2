#pragma once
#include "eirType.h"

#include <QRect>

#include <QList>
#include <QPoint>
#include <QSize>

class EIRTYPE_EXPORT QQRect : public QRect
{
public:
    typedef QList<QQRect> List;
public:
    QQRect();
    QQRect(const QSize size, const QPoint center);
};

