#pragma once

#include <QObject>

#include <eirBase/MultiName.h>
#include <eirBase/VarMap.h>

#include "Configuration.h"

class ConfigObject : public QObject
{
    Q_OBJECT
public:
    explicit ConfigObject(QObject *parent = nullptr);
    bool contains(const MultiName &key) const;
    bool equals(const Var &var) const;
    Var at(const MultiName &key);
    QVariant currentValue(const MultiName &key);
    QVariant defaultValue(const MultiName &key);
    bool isDefault(const MultiName &key) const;

signals:
    void varAdded(Var var);
    void varSet(Var var);
    void currentSet(Var var);
    void defaultSet(Var var);

public slots:
    void set(VarMap varMap);
    void set(Var var);
    void setDefault(Var var);
    void setDefault(MultiName key,
                    QVariant defaultVari);
    void setCurrent(Var var);
    void setCurrent(MultiName key,
                    QVariant currentVari);

protected slots:

private:
    Configuration mConfiguration;
};

