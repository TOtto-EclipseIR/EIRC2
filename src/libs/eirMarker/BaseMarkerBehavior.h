#pragma once

#include <QDir>

#include <eirType/BasicName.h>
#include <eirExe/Configuration.h>

class BaseMarker;
class MarkerManager;

class BaseMarkerBehavior
{
public:
    BaseMarkerBehavior(MarkerManager * manager,
                       const MultiName &configKey,
                       const QString &dirName);
    BaseMarker *marker() const;
    virtual BasicName name() const = 0;
    QDir dir() const;
    Configuration config();

private:
    MarkerManager * cmpManager=nullptr;
    QDir cmDir;
    Configuration mConfig;

};

