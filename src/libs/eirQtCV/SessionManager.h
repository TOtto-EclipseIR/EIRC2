#pragma once

#include <QObject>

#include <QHash>

#include <eirBase/MultiName.h>
#include <eirBase/MultiNameMap.h>
#include <eirBase/Uid.h>

#include "AbstractResource.h"

class Session;

class SessionManager : public QObject
{
    Q_OBJECT
public:
    explicit SessionManager(QObject *parent = nullptr);
    Uid registerResource(const MultiName &name,
                         AbstractResource *resource);

public:
    void connect(MultiName name);
    Uid resourceId(const MultiName &name);

signals:
    void connected(MultiName name, Uid sessionId);

private:
    QHash<Uid, Session *> mUidSessionMap;
    MultiNameMap mSessionNameMap;
    QHash<Uid, AbstractResource *> mUidResourceMap;
    MultiNameMap mResourceNameMap;
};

