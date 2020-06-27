#include "RectCascade.h"

#include <QFileInfo>

#include <eirBase/Debug.h>

#include "cvRectStdVector.h"

RectCascade::RectCascade(QObject *parent)
    : QObject(parent)
{
    TRACEFN;
}

bool RectCascade::load(const QString &fileName)
{
    TRACEQFI << fileName;
    close();
    mCascadeFileInfo = QFileInfo(fileName);
    TRACE << mCascadeFileInfo;
    mpCascade = new cvCascade(fileName.toStdString());
    TSTALLOC(mpCascade);
    DUMPVAL(mpCascade->empty());
    if ( ! mpCascade->empty())
        DUMPVAL(mpCascade->isOldFormatCascade());
    mCoreSize = QSize(32,32);
    NEEDDO(mCoreSize);
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
