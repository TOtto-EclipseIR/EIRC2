//! \file ImageFileQueueManager.h
#pragma once
#include "eirImage.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QMap>

#include <eirBase/BasicName.h>
#include <eirType/Sortable.h>

class ImageWriterQueue;
class ImageReaderQueue;
class ImageDirectoryQueue;

class ImageQueueManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageQueueManager(QObject *parent = nullptr);
    ImageWriterQueue *newWriterQueue(const BasicName &name,
                                     const QDir &dir);
    ImageReaderQueue *newReaderQueue(const BasicName &name,
                                     const QDir &dir);
    ImageDirectoryQueue *newDirectoryQueue(const BasicName &name,
                                           const QDir &dir);

signals:

public slots:

protected slots:

private:
    QMap<Sortable, ImageWriterQueue *> mNameWriterQueueMap;
    QMap<Sortable, ImageReaderQueue *> mNameReaderQueueMap;
    QMap<Sortable, ImageDirectoryQueue *> mNameDirectoryQueueMap;
};

