#pragma once
#include "eirType.h"

#include <QSize>

class EIRTYPE_EXPORT QQSize : public QSize
{
public:
    QQSize();
    QQSize(const QSize other);
    QQSize(const int width, const int height);
    QQSize(const int width, const int height, const int truncate);
    qreal aspect() const;
    int minDimension() const;
    int area() const;
    void setWidth(int width, qreal aspect);
    static QQSize null;
};

