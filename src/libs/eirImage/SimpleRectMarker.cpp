#include "SimpleRectMarker.h"

#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>

#include <eirObjDet/ObjectDetector.h>
#include <eirQtCV/cvCascade.h>
#include <eirType/QQSize.h>
#include <eirXfr/Debug.h>

SimpleRectMarker::SimpleRectMarker(const QQImage &inputImage)
    : QQImage(inputImage)
{
    TRACEQFI << inputImage;
}

void SimpleRectMarker::mark(const Configuration &markRectConfig,
                            const QQRectList &rectList,
                            const ObjDetPak &pak)
{
    TRACEQFI << rectList.vector();
    markRectConfig.dump();
    QPainter painter(this);
    QColor penColor = QColor(markRectConfig.string("PenColor","#7f00CCCC"));
    qreal penWidth = markRectConfig.real("PenWidth", 5.0);
    Qt::PenStyle penStyle = Qt::PenStyle(markRectConfig.unsignedInt("PenStyle", 1));
    QBrush penBrush(penColor);
    QPen pen(penBrush, penWidth, penStyle);
    painter.setPen(pen);
    painter.drawRects(rectList.vector());

    QColor sizeColor = QColor(markRectConfig.string("SizePenColor","#FFFF0000"));
    QPen sizePen(sizeColor);
    //QQSize imageSize = pak.inputImage().size();
    QQSize coreSize = pak.at("PreScan/CoreSize").toSize();
    int x = 16;
    painter.drawLine(x, 16, x, 24);
    x += coreSize.width();
    painter.drawLine(x, 16, x, 24);
    QVariant parmVari = pak.at("PreScan/Parameters");
    cvCascade::Parameters parms(parmVari);
    DUMP << parmVari;
    DUMP << parms.dumpList();
    qreal width = qreal(parms.minSize().width());
    qreal maxW  = qreal(parms.maxSize().width());
    qreal factor = parms.factor();
    TRACEQFI << width << maxW << factor;
    BEXPECTNOT(qIsNull(width));
    while (width < maxW)
    {
        x += width;
        painter.drawLine(x, 16, x, 24);
        width *= factor;
    }
    TRACEQFI << width << maxW << factor;
    painter.end();
}
