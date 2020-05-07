// file: {EIRC2 repo}./src/libs/eirQtCV/HaarRectangles.h
#pragma once
#include "eirQtCV4.h"

#include <QDir>
#include <QImage>
#include <QMultiMap>

#include <eirType/QQRectList.h>

class EIRQTCV4_EXPORT HaarRectangles
{
public:
    class HaarRectangleResult
    {
    public:
        void clear();
        void accumulate(QQRect detectRect);
        QQRect calculateCandidate() const;

    public:
        int rank;
        int quality;
        int area;
        int centerX;
        int centerY;
        QQRect candidate;
        QQRectList detected;
    };

public:
    explicit HaarRectangles();
    int count() const;
    bool isEmpty() const;
    void clear();
    void append(const QQRect rect);
    void append(const QQRectList rects);
    void operator << (const QQRect rect);
    void operator << (const QQRectList rects);

    void group();
    QList<HaarRectangleResult> groupedCandidates() const;
    QImage markCandidates(const QImage &frameImage,
                          const QFileInfo &fileInfo,
                          const QDir &candidateDir=QDir()) const;


private:
    QMultiMap<int /*area*/, QQRect> mRects;
    QMultiMap<int /*area*/, HaarRectangleResult> mGrouped;
    QQRectList mUnused;
};

