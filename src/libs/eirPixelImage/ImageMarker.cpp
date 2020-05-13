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
        QColor color, const int transparency,
        const int width)
{
    TRACEQFI << rectGroupResults.size()
             << color << transparency << width;
    if (mImage.isNull() || nullptr == mpPainter)
        return;
    mpPainter->begin(&mImage);
    QColor brushColor;
    QRgb rgb = color.rgb();
    brushColor.setRgb(qRed(rgb), qGreen(rgb), qBlue(rgb),
                           (100 - transparency) * 255 / 100);
//    TRACE << brushColor;
    foreach (HaarRectangles::HaarRectangleResult hhr, rectGroupResults)
    {
        QPen pen(brushColor, width);
        QPen pen1(brushColor, 1);
        mpPainter->setPen(pen1);
        mpPainter->drawRects(hhr.detected.vector());
        mpPainter->setPen(pen);
        mpPainter->drawRect(hhr.candidate);
        brushColor = brushColor.lighter(hhr.quality);
    }
    mpPainter->end();
}

void ImageMarker::markCandidatesOnly(const QList<HaarRectangles::HaarRectangleResult> &rectGroupResults, const QColor &color, const int transparency, const int width)
{
    TRACEQFI << rectGroupResults.size()
             << color << transparency << width;
    if (mImage.isNull() || nullptr == mpPainter)
        return;
    mpPainter->begin(&mImage);
    QColor brushColor;
    QRgb rgb = color.rgb();
    brushColor.setRgb(qRed(rgb), qGreen(rgb), qBlue(rgb),
                           (100 - transparency) * 255 / 100);
    TRACE << brushColor;
    QPen pen(brushColor, width);
    foreach (HaarRectangles::HaarRectangleResult hhr, rectGroupResults)
    {
        mpPainter->setPen(pen);
        mpPainter->drawRect(hhr.candidate);
    }
    WANTDO(overMark)
    mpPainter->end();
}

QImage ImageMarker::marked() const
{
    return mImage;
}
