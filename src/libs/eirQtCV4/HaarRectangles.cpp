// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.cpp
#include "HaarRectangles.h"

#include <QMutableMapIterator>

#include <cmath>

#include <eirXfr/Debug.h>
#include <eirType/Sortable.h>
#include <eirPixelImage/ImageMarker.h>

HaarRectangles::HaarRectangles() {TRACEFN}

void HaarRectangles::append(const QQRect rect)
{
    mRects.insert( - rect.area(), rect);
}

void HaarRectangles::append(const QQRectList rects)
{
    TRACEQFI << rects.size();
    foreach (QQRect rc, rects) append(rc);
}

void HaarRectangles::operator <<(const QQRect rect)
{
    append(rect);
}

void HaarRectangles::operator <<(const QQRectList rects)
{
    append(rects);
}
#if 0
void HaarRectangles::group()
{
    TRACEFN
    groupInnerOuter();
    groupGroups();
}

void HaarRectangles::groupInnerOuter()
{
    TRACEFN
    QQRectList rectList;
    QQRectList refillList;
    QQRectList orphanList;
    QList<HaarRectangleResult> nonOrphanList;
    HaarRectangleResult outerHrr; // Result for outer loop
    QQRect outerRect; // outer loop looking for similar rects
    QQRect innerRect; // inner loop subject rectangle

    //===== Outer Loop
    rectList = mRects.values();
    while ( ! rectList.isEmpty())
    {
        outerHrr.clear();
        refillList.clear();
        outerRect = rectList.takeFirst();
        outerHrr.candidate = outerRect;

        //===== InnerLoop
        while ( ! rectList.isEmpty())
        {
            innerRect = rectList.takeFirst();
            // TRACE << innerRect << rectList.size() << outerHrr.candidate;
            if (isSimilar(outerRect, innerRect))
                outerHrr.accumulate(innerRect);
            else
                refillList << innerRect;
        } // Inner Loop

        if (outerHrr.quality/*count*/ < 2)
            orphanList << outerHrr.candidate;
        else
            nonOrphanList << outerHrr;
        rectList << refillList;
        TRACE << outerRect
              << outerHrr.candidate << rectList.size();
    } // Outer Loop

    //===== Post Results
    mUnused = orphanList;
    foreach (HaarRectangleResult hrr, nonOrphanList)
        mGrouped.insert(hrr.area, hrr);
    TRACE << "exit groupInnerOuter()" << mGrouped.size();
}

void HaarRectangles::groupGroups()
{
    TRACEFN
    QList<HaarRectangleResult> hrrList;
    QList<HaarRectangleResult> refillList;
    QList<HaarRectangleResult> orphanList;
    QList<HaarRectangleResult> nonOrphanList;
    HaarRectangleResult outerHrr; // Result for outer loop
    HaarRectangleResult innerHrr; // Result for inner loop
    QQRect outerRect; // outer loop looking for similar rects
    QQRect innerRect; // inner loop subject rectangle

    //===== Outer Loop
    hrrList = mGrouped.values();
    while ( ! hrrList.isEmpty())
    {
        refillList.clear();
        outerHrr = hrrList.takeFirst();
        outerRect = outerHrr.candidate;

        //===== InnerLoop
        while ( ! hrrList.isEmpty())
        {
            innerHrr = hrrList.takeFirst();
            innerRect = innerHrr.candidate;
            if (isSimilar(outerRect, innerRect))
                outerHrr.merge(innerHrr);
            else
                refillList << innerHrr;
        } // Inner Loop

        if (outerHrr.quality/*count*/ < 2)
            orphanList << outerHrr;
        else
            nonOrphanList << outerHrr;
        hrrList << refillList;
    } // Outer Loop

    //===== Post Results
    foreach (HaarRectangleResult hrr, orphanList)
        mUnused << hrr.detected << hrr.candidate;
    mGrouped.clear();
    foreach (HaarRectangleResult hrr, nonOrphanList)
    {
        hrr.calculateCandidate();
        mGrouped.insert(hrr.area, hrr);
        TRACE << hrr.candidate << hrr.detected.size();
    }
} //  groupGroups()
#endif
// static
bool HaarRectangles::isSimilar(const QQRect rc1, const QQRect rc2)
{
    if ( ! rc1.intersects(rc2))     return false;
    qreal ratio = qreal(rc1.width()) / qreal(rc2.width());
    int centerDistance = qAbs(rc1.center().x() - rc2.center().x())
                              + qAbs(rc1.center().y() - rc2.center().y());
    if (ratio < 0.60 || ratio > 1.4)        return false;
    if (ratio > 1.0 && centerDistance > rc1.width())   return false;
    if (ratio < 1.0 && centerDistance > rc2.width())   return false;
    return true;
}

#if 0
QList<HaarRectangles::HaarRectangleResult>
    HaarRectangles::groupedCandidates() const
{
    TRACEQFI << mGrouped.size();
    return mGrouped.values();
}

QImage HaarRectangles::markCandidates(const QImage &frameImage,
                                      const QFileInfo &fileInfo,
                                      const QDir &candidateDir) const
{
    TRACEQFI << candidateDir;
    QImage rectImage = frameImage;
    ImageMarker marker(rectImage);
    marker.markCandidates(groupedCandidates());
    TRACE << "mUnused.size()" << mUnused.size();
    marker.markRectangles(mUnused, Qt::blue, 20, 1);
    NEEDDO(mUnused);
    if (candidateDir != QDir())
    {
        QFileInfo qfi(candidateDir,
                       fileInfo.fileName());
        TRACE << qfi;
        WEXPECT(marker.marked().save(qfi.filePath()));
    }
    return marker.marked();
}

QImage HaarRectangles::markAllCandidates(const QImage &frameImage, const QFileInfo &fileInfo, const QDir &candidateDir) const
{
    TRACEQFI << candidateDir;
    QImage rectImage = frameImage;
    ImageMarker marker(rectImage);
    marker.markAllCandidates(groupedCandidates());
    marker.markRectangles(mUnused, Qt::blue, 20, 1);
    if (candidateDir != QDir())
    {
        QFileInfo qfi(candidateDir,
                       fileInfo.fileName());
        TRACE << qfi;
        WEXPECT(marker.marked().save(qfi.filePath()));
    }
    return marker.marked();
}



void HaarRectangles::HaarRectangleResult::clear()
{
//    TRACEFN
    rank = quality = area = centerX = centerY = 0;
    candidate = QQRect();
    detected.clear();
}

void HaarRectangles::HaarRectangleResult::accumulate(
        QQRect detectRect)
{
    area += detectRect.area();
    centerX += detectRect.center().x();
    centerY += detectRect.center().y();
    detected.append(detectRect);
    quality = detected.size();
}

QQRect HaarRectangles::HaarRectangleResult
        ::calculateCandidate() const
{
    int nDetected = detected.size();
    int averageArea = area / nDetected;
    int averageDimension = qRound(sqrt(qreal(averageArea)));
    QQRect qqr(QSize(averageDimension, averageDimension),
                QPoint(centerX / nDetected,
                       centerY / nDetected));
    TRACEQFI << "n" << nDetected
             << "ta" << area << "aa" << averageArea << averageDimension
             << "tx" << centerX << "ax" << centerX / nDetected
             << "ty" << centerY << "ay" << centerY / nDetected
             << qqr;
    return qqr;
}
void HaarRectangles::HaarRectangleResult::merge(const HaarRectangles::HaarRectangleResult other)
{
    quality += other.quality; // count
    area += other.area;
    centerX += other.centerX;
    centerY += other.centerY;
    detected << other.detected;
}
#endif
