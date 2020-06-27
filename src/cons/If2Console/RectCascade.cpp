#include "RectCascade.h"

#include <QFileInfo>

#include <eirBase/Debug.h>

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

cvRect::Vector RectCascade::find(const qreal scaleFactor,
                                 const int minNeighbors,
                                 const cvSize minSize,
                                 const cvSize maxSize)
{
    NEEDDO(it); NEEDDO(return);
    NEEDUSE(scaleFactor);   NEEDUSE(minSize);
    NEEDUSE(minNeighbors);  NEEDUSE(maxSize);
    return cvRect::Vector();
}
