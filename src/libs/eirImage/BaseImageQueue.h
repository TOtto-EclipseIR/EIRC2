//! \file BaseImageQueue.h
#pragma once
#include "eirImage.h"

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QQueue>
#include <QMap>
#include <QString>

class ImageQueueObject;

class EIRIMAGE_EXPORT BaseImageQueue
{
public:
    BaseImageQueue(ImageQueueObject *imageQueueObject=nullptr);
    ImageQueueObject *queueObject();

    QQueue<QString> fileInfoQueue() const;
    void setFileInfoQueue(const QQueue<QString> &fileInfoQueue);

protected: // functions
    void setInputDir(const QDir &dir);
    void setOutputDir(const QDir &dir);
    bool isEmpty() const;
    int size() const;
    void contains(const QString &fileName) const;

protected: // data
    ImageQueueObject * mpQueueObject;
    QDir mInputDir;
    QDir mOutputDir;
    QQueue<QString> mFileNameQueue;
    QMap<QString, QImage> mFileNameImageMap;

private: // data

};

