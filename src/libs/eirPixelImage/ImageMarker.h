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
                    const int transparency=20,
                    const int width=1);
    void markCandidates(const QList<HaarRectangles::
                        HaarRectangleResult> & rectGroupResults,
                    QColor color=Qt::green,
                    const int transparency=20,
                    const int width=7);
    void markCandidatesOnly(const QList<HaarRectangles::
                        HaarRectangleResult> & rectGroupResults,
                    const QColor & color=Qt::green,
                    const int transparency=20,
                    const int width=7);
    QImage marked(void) const;

private:
    QImage mImage;
    QPainter *mpPainter=nullptr;
};

