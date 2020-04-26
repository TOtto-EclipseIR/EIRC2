// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.h
#pragma once
#include "eirQtCV4.h"

#include <QMap>

#include <eirType/QQRectList.h>

class EIRQTCV4_EXPORT HaarRectangles
{
public:
    explicit HaarRectangles();
    int count() const;
    bool isEmpty() const;
    void clear();
    void append(const QQRect rect);
    void append(const QQRectList rects);
    void operator << (const QQRect rect);
    void operator << (const QQRectList rects);

private:
    QMap<int /*area*/, QQRect> mRects;
};

