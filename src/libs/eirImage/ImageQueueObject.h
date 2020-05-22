//! \file ImageQueueObject.h
#pragma once
#include "eirImage.h"

#include <QObject>

#include <QFileInfo>
#include <QImage>

class ImageQueueObject : public QObject
{
    Q_OBJECT
public:
    explicit ImageQueueObject(QObject *parent = nullptr);
    void emitQueueEmpty();
    void emitQueueChanged(int size);
    void emitEnqueued(QFileInfo fileInfo, QImage image);
    void emitDequeued(QFileInfo fileInfo, QImage image);


signals:
    void queueEmpty();
    void queueChanged(int size);
    void enqueued(QFileInfo fileInfo, QImage image);
    void dequeued(QFileInfo fileInfo, QImage image);

};

