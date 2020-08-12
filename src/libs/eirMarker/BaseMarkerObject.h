#pragma once

#include <QObject>

#include "AbstractMarkerInterface.h"

class BaseMarkerObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseMarkerObject(AbstractMarkerInterface *behavior,
                              QObject *parent = nullptr);
    MultiName markerName() const;
    AbstractMarkerInterface *behavior() const;

signals:

private:
    AbstractMarkerInterface *cmpBehavior=nullptr;
};

