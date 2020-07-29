#pragma once

#include <QObject>

#include <QDir>
#include <QString>

#include <eirType/BasicName.h>
#include <eirType/MultiName.h>
#include <eirExe/Configuration.h>

class BaseMarkerBehavior;
class MarkerManager;

class BaseMarker : public QObject
{
    Q_OBJECT
public:
    explicit BaseMarker(BaseMarkerBehavior *behavior,
                        MarkerManager *manager,
                        const BasicName &markedName,
                        const QDir &dir,
                        const Configuration &markerConfig);
    BasicName name() const;
    QDir dir() const;

signals:

private:
};

