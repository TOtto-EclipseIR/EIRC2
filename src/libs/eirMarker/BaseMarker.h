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
    explicit BaseMarker(MarkerManager *manager,
                        BaseMarkerBehavior *behavior,
                        const BasicName &markedName,
                        const QDir &dir,
                        const Configuration &markerConfig);
    QDir dir() const;

signals:

private:
    MarkerManager * cmpManager=nullptr;
    BasicName cmMarkedName;
    BaseMarkerBehavior * cmpBehavoir;
    QDir cmDir;
    MultiName cmConfigKey;
    Configuration mMarkerConfig;
};

