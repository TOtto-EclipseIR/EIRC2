#pragma once
#include "eirType.h"

#include <QSize>

class EIRTYPE_EXPORT QQSize : public QSize
{
public:
    QQSize();
    QQSize(const QSize other);
    QQSize(const int width, const int height, const int truncate);
    int area() const;

};

