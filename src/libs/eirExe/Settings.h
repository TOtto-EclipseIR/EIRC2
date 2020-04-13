// file: {repo: EIRC2}./src/libs/eirExe/Settings.h
#pragma once
#include "eirExe.h"

#include <QObject>
#include <QSettings>

#include <eirBase/MultiName.h>
#include <eirBase/Var.h>
#include <eirBase/VarMap.h>

class ApplicationHelper;

class EIREXE_EXPORT Settings : protected QSettings
{
    Q_OBJECT
public:
    explicit Settings(ApplicationHelper *parent);
    ApplicationHelper * helper();
    void set(const MultiName &key,
             const QVariant &value);
    void addWatch(const MultiName &key);
    void addWatchlist(const MultiName::List &keys);
    QVariant value(const MultiName &key,
                  const QVariant &fallback=QVariant()) const;

signals:
    void opened(QString path);
    void watchedChanged(MultiName key, QVariant value);
    void changed(Var var);

private slots:

private:
    ApplicationHelper * mpHelper=nullptr;
    MultiName::List mWatchList;
};

