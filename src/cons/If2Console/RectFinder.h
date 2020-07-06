#pragma once

#include <QImage>
#include <QList>
#include <QPen>
#include <QRect>

#include "cvMat.h"
#include "cvRect.h"
#include "cvRectStdVector.h"
#include "RectCascade.h"
#include "RectFinderClass.h"
#include "RectFinderParameters.h"

typedef QList<QRect> RectList;

class RectFinder
{
public:
    RectFinder(RectCascade *cascade=nullptr);
    QSize coreSize() const;
    void clearImage();
    bool loadImage(const QString &inputfileName);
    QSize inputSize() const;
    int find(RectFinderParameters parms);
    QImage inputImage(const QImage::Format format=QImage::Format_RGB32);
    QImage detectImage(const QImage::Format format=QImage::Format_Grayscale8);
    QImage rectImage(const QPen pen=QPen(QBrush(Qt::blue), 1),
                     const QImage::Format format=QImage::Format_RGB32);
    cvRect::Vector cvRectVector() const;
    RectList rectList() const;

protected:
    int fillRectList(const cvRectStdVector & cvVector);

private:
    RectCascade * cmpCascade=nullptr;
    cvMat mInputMat;
    QImage mInputImage;
    QImage mDetectImage;
    QImage mRectImage;
    RectList mRectList;
};

