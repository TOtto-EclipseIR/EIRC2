#pragma once

#include <QSize>

#include "QQRect.h"
#include "QQRectF.h"

class Region : public QQRect
{
public:
    Region();
    Region(const QQRectF rcf);
    Region(const QQRectF rcf, const QSize sz);
    QQRect set(const QSize sz);
    QQRect set(const QQRectF rcf, const QSize sz);

private:
    QQRectF mRectF;
    QSize mSize;
    QQRect mRegion;
};

