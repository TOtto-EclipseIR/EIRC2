#include "RectCascade.h"

#include <QFileInfo>

#include <eirBase/Debug.h>

#include "cvRectStdVector.h"

RectCascade::RectCascade(QObject *parent)
    : QObject(parent)
{
    TRACEFN;
}

bool RectCascade::load(const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo.absoluteFilePath();
    close();
    mCascadeFileInfo = fileInfo;
    mpCascade = new cvCascade(fileInfo
        .absoluteFilePath().toStdString());
    TSTALLOC(mpCascade);
    DUMPVAL(mpCascade->empty());
    DUMPVAL(mpCascade->isOldFormatCascade());
    if (isEmpty())
        close();
    else
        mCoreSize = QSize(32,32); NEEDDO(mCoreSize);
    return ! mpCascade->empty();
}

QSize RectCascade::coreSize() const
{
    return mCoreSize;
}

void RectCascade::close()
{
    TRACEFN;
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
    mCascadeFileInfo = QFileInfo();
    mCoreSize = QSize();
}

bool RectCascade::isEmpty() const
{
    TSTALLOC(mpCascade);
    return mpCascade->empty();
}

cvRectStdVector RectCascade::find(const cvMat &inputMat,
                                 const qreal scaleFactor,
                                 const int minNeighbors,
                                 const cvSize minSize,
                                 const cvSize maxSize)
{
    TRACEQFI << scaleFactor << minNeighbors
             << minSize << maxSize;
    TSTALLOC(mpCascade);
    cvRectStdVector rects;
    mpCascade->detectMultiScale(inputMat.mat(),
                                rects.toCvRectStdVector(),
                                scaleFactor,
                                minNeighbors,
                                0, // flags now unused?!
                                minSize,
                                maxSize);
    NEEDDO(it); NEEDDO(return);
    NEEDUSE(scaleFactor);   NEEDUSE(minSize);
    NEEDUSE(minNeighbors);  NEEDUSE(maxSize);
    return rects;
}
