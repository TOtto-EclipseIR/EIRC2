#include "SimpleRectMarker.h"

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include <eirXfr/Debug.h>

SimpleRectMarker::SimpleRectMarker(const QQImage &inputImage)
    : QQImage(inputImage)
{
    TRACEQFI << inputImage;
}

void SimpleRectMarker::mark(const Configuration &markRectConfig,
                            const QQRectList &rectList)
{
    TRACEQFI << rectList.vector();
    markRectConfig.dump();
    QPainter painter(this);
    QColor penColor = QColor(markRectConfig.string("PenColor","#7f00CCCC"));
    qreal penWidth = markRectConfig.real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectConfig.unsignedInt("PenStyle", 2));
    QBrush penBrush(penColor);
    QPen pen(penBrush, penWidth, penStyle);
    painter.setPen(pen);
    painter.drawRects(rectList.vector());
    painter.end();
}
