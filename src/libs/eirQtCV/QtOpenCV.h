#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QMap>

#include <eirType/Enumeration.h>

#include "Configurations.h"

#define OBJECTTYPE_ENUM(NV) \
    NV(Null, = 0)  \
    NV(FrontalFace,)   \
    NV(LeftEye,) \
    NV(RightEye,) \
    NV(EitherEye,) \
    NV(BothEyes,) \

class EIRQTCV_EXPORT ObjectType : public Enumeration
{
    DECLARE_ENUMERATION(ObjectType, OBJECTTYPE_ENUM)
};

class HaarCascade;

class EIRQTCV_EXPORT QtOpenCV : public QObject
{
    Q_OBJECT
public:
    explicit QtOpenCV(QObject *parent = nullptr);

private slots:
    void setDefaultConfiguration();
    void setOverideConfiguration();
    void createFrontalFace();

private:
    bool createCascade(const ObjectType objType,
                       const VarMap &config);

signals:
    void defaultConfigurationLoaded();
    void cascadeError(ObjectType objType, QStringList messages);
    void cascadeCreated(ObjectType objType);

private:
    Configurations mConfigurations;
    QMap<ObjectType, HaarCascade *> mTypeCascadeMap;
};

