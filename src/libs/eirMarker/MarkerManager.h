#pragma once
#include "eirMarker.h"

#include <QObject>

#include <QDir>
#include <QImage>
#include <QMap>
#include <QString>

#include <eirType/MultiName.h>
#include <eirExe/ConfigObject.h>

class BaseMarker;

class MarkerManager : public QObject
{
    Q_OBJECT
public:
    explicit MarkerManager(QObject *parent = nullptr);

protected: // slots:
    void setupMarkerNameList();
    void setupNameKeyMap();
    void configure(ConfigObject * cfgObj);
    void setBaseDir(QString baseDir);
    void setMarkedDir(MultiName markerName,
                      QString markerDirName);

signals:

private:
    Configuration mConfig;
    QDir mBaseDir;
    MultiName::List mMarkerNameList;
    QMap<MultiName, MultiName> mNameKeyMap;
    QMap<MultiName, BaseMarker *> mNameMarkerMap;
    QMap<MultiName, QImage> mNameImageMap;
};

