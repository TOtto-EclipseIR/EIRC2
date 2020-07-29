#pragma once
#include "eirMarker.h"

#include <QObject>

#include <QDir>
#include <QImage>
#include <QMap>
#include <QString>

#include <eirType/BasicName.h>
#include <eirType/MultiName.h>
#include <eirExe/ConfigObject.h>

class BaseMarker;
class BaseMarkerBehavior;
class ConfigObject;

class EIRMARKER_EXPORT MarkerManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkerManager(ConfigObject *cfgObj,
                           QObject *parent = nullptr);
    QDir baseDir() const;
    QDir markerDir(const QString markerDirName);
    ConfigObject * cfgObj();
    Configuration markerConfig() const;
    Configuration markerConfig(const MultiName &groupKey) const;
    BasicName::List markedNameList() const;
    void setupMarkerDir(const BasicName &markerName,
                        BaseMarkerBehavior *behavior,
                        const MultiName &markerConfigGroup,
                        const QString &markerDirName);

protected slots:
    void setBaseDir(QDir baseDir);
    void setBaseDir(QString baseDirName);
    void setupMarkers();

signals:
    void markedDirSet(BasicName markerName,
                      QDir markerDir);

private:
    ConfigObject * const cmpConfig=nullptr;
    const Configuration cmMarkerConfig;
    QDir mBaseDir;
    BasicName::List mMarkedNameList;
    QMap<BasicName, QDir> mMarkedNameDirMap;
    QMap<BasicName, MultiName> mMarkedNameConfigKeyMap;
    QMap<BasicName, BaseMarker *> mMarkedNameMarkerMap;
    QMap<BasicName, QImage> mMarkedNameImageMap;
};

