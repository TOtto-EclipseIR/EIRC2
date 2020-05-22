//! \file BaseImageQueue.h
#pragma once
#include "eirImage.h"

#include <QFileInfo>
#include <QImage>
#include <QQueue>
#include <QMap>
#include <QString>

class ImageQueueObject;

class EIRIMAGE_EXPORT BaseImageQueue
{
public:
    BaseImageQueue(const QFileInfo &fileInfo,
                   ImageQueueObject *imageQueueObject);
    ImageQueueObject *queueObject();

protected: // functions
    bool isEmpty() const;
    int size() const;
    void contains(const QFileInfo &fileInfo) const;
    QFileInfo peekFirstFileInfo() const;
    QImage peekFirstImage() const;
    QFileInfo dequeueFileInfo();
    void dequeueVoid();
    QImage takeImage(const QFileInfo &fileInfo);
    void enqueue(const int recurseDepth=0);
    void enqueue(const QString &fileName,
                 const QImage &image);
    void enqueue(const QFileInfo &fileInfo,
                 const QImage &image);

public slots:

protected slots:

protected: // data
    const QFileInfo cmFileInfo;
    ImageQueueObject * mpQueueObject;
    QQueue<QFileInfo> mFileInfoQueue;
    QMap<QFileInfo, QImage> mFileInfoImageMap;

private: // data

};

