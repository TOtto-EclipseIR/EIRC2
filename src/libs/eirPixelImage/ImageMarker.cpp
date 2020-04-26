// file: {EIRC2 repo)./src/libs/eirType/ImageMarker.cpp
#include "ImageMarker.h"

#include <QColor>
#include <QPainter>

#include <eirBase/Debug.h>
#include <eirType/QQRectList.h>

ImageMarker::ImageMarker(const QImage &image)
    : mImage(image)
    , mpPainter(new QPainter())
{
    TRACEQFI << image;
}

void ImageMarker::markRectangles(const QQRectList &rectangles,
                             const QColor & color,
                             const int width)
{
    TRACEQFI << rectangles << color << width;
    if (mImage.isNull() || nullptr == mpPainter)
        return;
    mpPainter->begin(&mImage);
    mpPainter->setPen(QPen(QBrush(color), width));
    mpPainter->drawRects(rectangles.vector());
    mpPainter->end();
}

QImage ImageMarker::marked() const
{
    return mImage;
}
