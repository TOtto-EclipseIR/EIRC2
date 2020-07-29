#include "MarkerManager.h"
#include "eirMarker.h"

#include <eirXfr/Debug.h>

#include "BaseMarker.h"

MarkerManager::MarkerManager(ConfigObject *cfgObj,
                             QObject *parent)
    : QObject(parent)
    , cmpConfig(cfgObj)
    , cmMarkerConfig(cfgObj->configuration("Marker"))
{
    TRACEQFI << QOBJNAME(parent) << QOBJNAME(cfgObj);
    TSTALLOC(cmpConfig);
    cmMarkerConfig.dump();
}

QDir MarkerManager::baseDir() const
{
    TRACEQFI << mBaseDir;
    return mBaseDir;
}

QDir MarkerManager::markerDir(const QString markerDirName)
{
    TRACEQFI << markerDirName;
    QDir dir = baseDir();
    dir.mkpath(markerDirName);
    dir.cd(markerDirName);
    TODO(exists-writable);
    TRACE << dir;
    return dir;
}

Configuration MarkerManager::markerConfig() const
{
    return cmMarkerConfig;
}

Configuration MarkerManager::markerConfig(const MultiName &groupKey) const
{
    return markerConfig().extract(groupKey);
}

void MarkerManager::setupMarkerDir(const BasicName &markerName,
                                   BaseMarkerBehavior * behavior,
                                   const MultiName &markerConfigGroup,
                                   const QString &markerDirName)
{
    TRACEQFI << markerName() << markerConfigGroup() << markerDirName;
    QDir dir = markerDir(markerDirName);
    Configuration config = markerConfig(markerName);
    BaseMarker baseMarker(this, behavior, markerName, dir, config);
    EMIT(markedDirSet(markerName, dir));
}

void MarkerManager::setBaseDir(QDir baseDir)
{
    mBaseDir = baseDir;
}

void MarkerManager::setBaseDir(QString baseDirName)
{
    mBaseDir = QDir::current();
    mBaseDir.mkpath(baseDirName);
    mBaseDir.cd(baseDirName);
}

void MarkerManager::setupMarkers()
{

}

