#pragma once

#include <QObject>

#include <eirType/MultiName.h>

class BaseMarker : public QObject
{
    Q_OBJECT
public:
    explicit BaseMarker(const MultiName &markerName,
                        QObject *parent = nullptr);
    bool setDir(const QString &dirName);

signals:

private:

};

