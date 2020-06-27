#include "RectFinder.h"

#include <QImage>

#include <eirBase/Debug.h>

RectFinder::RectFinder(RectCascade *cascade)
    : cmpCascade(cascade)
{
    TRACEFN;

}

bool RectFinder::loadImage(const QString &inputfileName)
{
    mInputMat.set(cv::imread(inputfileName.toStdString()));
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
    cvRect::Vector cvRectVector =
            cmpCascade->find(parms.scaleFactor(),
                             parms.minNeighbors(),
                             parms.minSize(),
                             parms.maxSize());
    return fillRectList(cvRectVector);
}

QImage RectFinder::inputImage(const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(format); NEEDDO(return);
    return QImage();
}

QImage RectFinder::detectImage(const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(format); NEEDDO(return);
    return QImage();
}

QImage RectFinder::rectImage(const QPen pen, const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(pen); NEEDUSE(format); NEEDDO(return);
    return QImage();
}

RectList RectFinder::rectList() const
{
    return mRectList;
}

int RectFinder::fillRectList(const cvRect::Vector &cvVector)
{
    mRectList.clear();
    foreach (cvRect cvrc, cvVector)
        mRectList.append(QRect(cvrc));
    return mRectList.size();
}

