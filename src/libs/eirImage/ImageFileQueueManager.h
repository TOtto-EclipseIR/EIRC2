//! \file ImageFileQueueManager.h
#pragma once
#include "eirImage.h"

#include <QObject>

#include <QFileInfo>
#include <QMap>

#include <eirBase/BasicName.h>

class ImageWriterQueue;
class ImageReaderQueue;
class ImageDirectoryQueue;

class ImageFileQueueManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageFileQueueManager(QObject *parent = nullptr);
    ImageWriterQueue * newWriterQueue(const QFileInfo &fileInfo);
    ImageReaderQueue * newReaderQueue(const QFileInfo &fileInfo);
    ImageDirectoryQueue * newDirectoryQueue(const QFileInfo &fileInfo);

signals:

public slots:

protected slots:

private:
    QMap<QFileInfo, ImageWriterQueue *> mWriterQueueMap;
    QMap<QFileInfo, ImageReaderQueue *> mReaderQueueMap;
    QMap<QFileInfo, ImageDirectoryQueue *> mDirectoryQueueMap;
};

