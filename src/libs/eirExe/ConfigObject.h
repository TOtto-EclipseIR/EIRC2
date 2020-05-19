#pragma once

#include <QObject>

#include <eirBase/VarMap.h>

class ConfigObject : public QObject
{
    Q_OBJECT
public:
    explicit ConfigObject(QObject *parent = nullptr);

signals:

public slots:

protected slots:

private:
    VarMap mConfig;
};

