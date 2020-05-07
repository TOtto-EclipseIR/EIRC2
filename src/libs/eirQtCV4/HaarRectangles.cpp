// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.cpp
#include "HaarRectangles.h"

#include <cmath>

#include <eirBase/Debug.h>
#include <eirPixelImage/ImageMarker.h>

HaarRectangles::HaarRectangles() {TRACEFN}

void HaarRectangles::append(const QQRect rect)
{
    //TRACEQFI << rect;
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

void HaarRectangles::group()
{
    TRACEFN
    QMutableMapIterator<int, QQRect> i(mRects);
    HaarRectangleResult hrr;
    while ( ! mRects.isEmpty())
    {
        TRACE << "mRects.size()" << mRects.size();
        hrr.clear();
        i.toFront();
        if ( ! i.hasNext()) break;              //----------
        i.next();
        QQRect outerRect = i.value();
        hrr.accumulate(outerRect);
        int minInnerArea = i.key() - (i.key() >> 2);
        TRACE << "outerRect" << outerRect << i.key() << minInnerArea;
        i.remove();
//        EXPECT(i.hasNext())
  //      if ( ! i.hasNext()) break;              //----------
//        i.next();
  //      TRACE << "middleRect" << i.value() << i.key();
        while (i.hasNext())
        {
            i.next();
            if (i.key() > minInnerArea) break;  //----------
            if ( ! outerRect.intersects(i.value()))
                continue;                       //==========
            if (outerRect.overlap(i.value()) > 0.70)
            {
                TRACE << "innerRect" << i.value() << i.key()
                      << outerRect.overlap(i.value());
                hrr.accumulate(i.value());
                i.remove();
            }
        }
        if (hrr.quality /*count*/ > 16)
        {
            hrr.candidate = hrr.calculateCandidate();
            hrr.rank = mGrouped.size() + 1;
            mGrouped.insert(hrr.area / hrr.detected.size(), hrr);
            TRACE << "rank" << hrr.rank;
        }
        else
        {
            TRACE << "mUnused" << hrr.detected.first();
            mUnused << hrr.detected.takeFirst();
            append(hrr.detected);
        }
    }
    mUnused = mRects.values();
}

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
    marker.markRectangles(mUnused, Qt::black, 50, 1);
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
    TRACEFN
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
