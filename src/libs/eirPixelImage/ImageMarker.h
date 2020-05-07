// file: {EIRC2 repo)./src/libs/eirType/ImageMarker.h
#pragma once
#include "eirPixelImage.h"

#include <QImage>
class QColor;
class QPainter;
class QQRectList;

#include <eirType/QQRect.h>
#include <eirQtCV4/HaarRectangles.h>

class EIRPIXELIMAGE_EXPORT ImageMarker
{
public:
    ImageMarker(const QImage &image=QImage());
    void markRectangles(const QQRectList & markRectangles,
                    const QColor & color=Qt::blue,
#ifdef QT_NO_DEBUG // Release
                    const int transparency=50,
                    const int width=3);
#else // Debug
                    const int transparency=75,
                    const int width=1);
#endif
    void markCandidates(const QList<HaarRectangles::
                        HaarRectangleResult> & rectGroupResults,
                    const QColor & color=Qt::green,
                    const int transparency=50,
                    const int width=7);
    QImage marked(void) const;

private:
    QImage mImage;
    QPainter *mpPainter=nullptr;
};

