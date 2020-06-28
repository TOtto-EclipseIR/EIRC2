#include "RectFinder.h"

#include <QImage>
#include <QPainter>

#include <eirBase/Debug.h>

RectFinder::RectFinder(RectCascade *cascade)
    : cmpCascade(cascade)
{
    TRACEFN;

}

QSize RectFinder::coreSize() const
{
    TSTALLOC(cmpCascade);
    return cmpCascade->coreSize();
}

void RectFinder::clear()
{
    mInputMat = cvMat();
    mInputImage = QImage();
    mDetectImage = QImage();
    mRectImage = QImage();
}

bool RectFinder::loadImage(const QString &inputfileName)
{
    clear();
    mInputMat.load(QFileInfo(inputfileName));
    return ! mInputMat.isEmpty();
}

QSize RectFinder::inputSize() const
{
    return QSize(mInputMat.cols(), mInputMat.rows());
}

int RectFinder::find(RectFinderParameters parms)
{
    TRACEFN;
    TSTALLOC(cmpCascade);
    BEXPECTNOT(cmpCascade->isEmpty());
    parms.calculate(inputSize());
    cvRectStdVector rectVector =
            cmpCascade->find(mInputMat,
                             parms.scaleFactor(),
                             parms.minNeighbors(),
                             parms.minSize(),
                             parms.maxSize());
    return fillRectList(rectVector);
}

QImage RectFinder::inputImage(const QImage::Format format)
{
    if ( ! mInputImage.isNull())    return mInputImage;

    NEEDDO(it); NEEDUSE(format); NEEDDO(return);

    return QImage();
}

QImage RectFinder::detectImage(const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(format); NEEDDO(return);
    return QImage();
}

QImage RectFinder::rectImage(const QPen pen,
                             const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(pen); NEEDUSE(format); NEEDDO(return);
    if ( ! mRectImage.isNull()) return mRectImage;
    QImage rectImage = detectImage();
    QPainter painter;
    painter.begin(&rectImage);

    painter.end();
    return mRectImage = rectImage;
}

RectList RectFinder::rectList() const
{
    return mRectList;
}

int RectFinder::fillRectList(const cvRectStdVector &cvVector)
{
    WANTDO(Move to rectCascade);
    mRectList.clear();
    foreach (cvRect cvrc, cvVector.toCvRectStdVector())
        mRectList.append(QRect(cvrc));
    return mRectList.size();
}

