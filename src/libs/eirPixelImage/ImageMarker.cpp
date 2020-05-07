// file: {EIRC2 repo)./src/libs/eirType/ImageMarker.cpp
#include "ImageMarker.h"

#include <QColor>
#include <QPainter>

#include <eirBase/Debug.h>
#include <eirType/QQRectList.h>

ImageMarker::ImageMarker(const QImage &image)
    : mpPainter(new QPainter())
{
    TRACEQFI << image;
    mImage = image.convertToFormat(QImage::Format_ARGB32);
}

void ImageMarker::markRectangles(const QQRectList &rectangles,
                                 const QColor & color,
                                 const int transparency,
                                 const int width)
{
    TRACEQFI << rectangles.size()
             << color << transparency << width;
    if (mImage.isNull() || nullptr == mpPainter)
        return;
    QRgb rgb = color.rgb();
    QColor brushColor;
    brushColor.setRgb(qRed(rgb), qGreen(rgb), qBlue(rgb),
                           (100 - transparency) * 255 / 100);
    TRACE << brushColor;
    QPen pen(brushColor, width);
    mpPainter->begin(&mImage);
    mpPainter->setPen(pen);
    mpPainter->drawRects(rectangles.vector());
    mpPainter->end();
}

void ImageMarker::markCandidates(const QList<HaarRectangles::
        HaarRectangleResult> &rectGroupResults,
        const QColor &color, const int transparency,
        const int width)
{
    TRACEQFI << rectGroupResults.size()
             << color << transparency << width;
    if (mImage.isNull() || nullptr == mpPainter)
        return;
    mpPainter->begin(&mImage);
    QColor brushColor;
    QColor brushColor0;
    QColor brushColor1;
    QRgb rgb = color.rgb();
    QRgb rgb1 = QColor(Qt::blue).rgb();
    QRgb rgb0 = QColor(Qt::black).rgb();
    brushColor.setRgb(qRed(rgb), qGreen(rgb), qBlue(rgb),
                           (100 - transparency) * 255 / 100);
    TRACE << brushColor;
    brushColor1.setRgb(qRed(rgb1), qGreen(rgb1), qBlue(rgb1),
                           (100 - transparency) * 255 / 100);
    brushColor0.setRgb(qRed(rgb0), qGreen(rgb0), qBlue(rgb0),
                           (100 - transparency) * 255 / 100);
    QPen pen(brushColor, width);
    QPen pen1(brushColor1, 1);
    QPen pen0(brushColor0, 1);
    foreach (HaarRectangles::HaarRectangleResult hhr, rectGroupResults)
    {
        mpPainter->setPen(pen1);
        mpPainter->drawRects(hhr.detected.vector());
        mpPainter->setPen(pen);
        mpPainter->drawRect(hhr.candidate);
    }
    mpPainter->end();
}

QImage ImageMarker::marked() const
{
    return mImage;
}
