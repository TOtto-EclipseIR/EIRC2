#pragma once

#include <QObject>
#include "SessionManager.h"

#include <eirBase/VarPak.h>

class AbstractResource : public SessionManager
{
    Q_OBJECT

public:
    enum Class
    {
        nullResource = 0,
        HaarCascade,
        sizeResource
    };

public:
    explicit AbstractResource(const Class resourceClass,
                              const MultiName &name,
                              QObject *parent = nullptr);
    Class resourceClass() const;

private:
    virtual void doInitialize() = 0;
    virtual void doLoad() = 0;
    virtual void doConfigure() = 0;

public slots:
    void initialize(VarPak initData);
    void load(VarPak loadData);
    void configure(VarPak config);


signals:
    void initialized(Uid resourceId);
    void loaded(Uid resourceId);
    void configured(Uid resourceId);

private:
    const Class cmResourceClass;
    const Uid cmResourceId;
    const MultiName cmResourceName;
    VarPak mInitData;
    VarPak mLoadData;
    VarPak mConfig;
};

