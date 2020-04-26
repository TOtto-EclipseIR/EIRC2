// file: {EIRC2 repo)./src/libs/eirType/ImageMarker.h
#pragma once
#include "eirPixelImage.h"

#include <QImage>
class QColor;
class QPainter;
class QQRectList;

#include <eirType/QQRect.h>

class EIRPIXELIMAGE_EXPORT ImageMarker
{
public:
    ImageMarker(const QImage &image=QImage());
    void markRectangles(const QQRectList & markRectangles,
                    const QColor & color=Qt::blue,
                    const int width=1);
    QImage marked(void) const;

private:
    QImage mImage;
    QPainter *mpPainter=nullptr;
};

