#pragma once

#include <QObject>

#include <QHash>

#include <eirBase/Uid.h>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = nullptr);

signals:


private:
    static QHash<Uid, Session *> mUidSessionMap;
};

