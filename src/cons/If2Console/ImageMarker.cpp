#include "ImageMarker.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include <eirBase/Debug.h>
#include <eirExe/ConfigObject.h>

#include "ImageMarker.h"

ImageMarker::ImageMarker()
    : mpConfig(new ConfigObject())
{

}

QImage ImageMarker::markRetangles(const QImage inImage,
                                  const QList<QRect> rectList,
                                  const int transparencyPerK,
                                  const QColor penColor,
                                  const int penWidth)
{
    TRACEQFI << inImage.size() << rectList.size()
             << transparencyPerK << penColor << penWidth;

    QImage outImage = inImage.convertToFormat(QImage::Format_ARGB32);
    QPainter painter(&outImage);
    QBrush brush(penColor);
    QPen pen(brush, penWidth);
    painter.setPen(pen);
    foreach (QRect rc, rectList)
        painter.drawRect(rc);
    painter.end();
    return outImage;
}
