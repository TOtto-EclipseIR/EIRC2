#pragma once

#include <QObject>

#include <QHash>

#include <eirBase/MultiNameMap.h>
#include <eirBase/Uid.h>

class Session : public QObject
{
    Q_OBJECT
public slots: // static
    static void connect(const MultiName *name,
                        QObject * parent);
    static void load(Uid sessionId, Uid resourceId);
    static void load(Uid sessionId, MultiName resourceName);
    static void unload(Uid sessionId, Uid resourceId);

public: // static
    static Uid registerResource(MultiName name);

public slots:
    void disconnect(const Uid sessionId);
    void load(Uid resourceId);
    void load(MultiName resourceName);
    void unload(Uid resourceId);

signals:
    void connected(MultiName name, Uid sessionUid);
    void disconnected(MultiName name, Uid sessionUid);

private:
    explicit Session(QObject *parent = nullptr);


private:
    Uid mUid;
    MultiName mName;
};

