#pragma once

#include <QObject>

#include <QGraphicsScene>

#include <eirFrame/FramePak.h>

class MarkerImage : public QObject
{
    Q_OBJECT
public:
    explicit MarkerImage(const FramePak &pak,
                         QObject *parent = nullptr);

signals:


private:
    FramePak cmFramePak;
    QGraphicsScene mScene;
};

