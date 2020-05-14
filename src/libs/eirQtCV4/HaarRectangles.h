// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.h
#pragma once
#include "eirQtCV4.h"

#include <QDir>
#include <QImage>
#include <QMultiMap>

#include <eirType/QQRectList.h>
//#include <eirPixelImage/ImageMarker.h>

class EIRQTCV4_EXPORT HaarRectangles
{
#if 0
public:
    class HaarRectangleResult
    {
    public:
        void clear();
        void accumulate(QQRect detectRect);
        QQRect calculateCandidate() const;
        void merge(const HaarRectangleResult other);

    public:
        int rank;
        int quality;
        int area;
        int centerX;
        int centerY;
        QQRect candidate;
        QQRectList detected;
    };
#endif

public:
    explicit HaarRectangles();
    int count() const;
    bool isEmpty() const;
    void clear();
    void append(const QQRect rect);
    void append(const QQRectList rects);
    void operator << (const QQRect rect);
    void operator << (const QQRectList rects);
#if 0
    QList<HaarRectangleResult> groupedCandidates() const;
    void group();
    QImage markCandidates(const QImage &frameImage,
                          const QFileInfo &fileInfo,
                          const QDir &candidateDir=QDir()) const;
    QImage markAllCandidates(const QImage &frameImage,
                          const QFileInfo &fileInfo,
                          const QDir &candidateDir=QDir()) const;

private:
    void groupInnerOuter();
    void groupGroups();
#endif
    static bool isSimilar(const QQRect rc1, const QQRect rc2);





private:
    QMultiMap<int /*area*/, QQRect> mRects;
//    QMultiMap<int /*area*/, HaarRectangleResult> mGrouped;
    QQRectList mUnused;
};

