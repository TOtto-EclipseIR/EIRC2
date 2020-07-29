#pragma once

#include <QObject>

class BaseMarkerBehavior;

class Marker : public QObject
{
    Q_OBJECT
public:
    explicit Marker(BaseMarkerBehavior *behavior,
                     QObject *parent = nullptr);

signals:

};

