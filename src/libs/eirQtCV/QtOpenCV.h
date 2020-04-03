#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QMap>

#include <eirType/Enumeration.h>
#include <eirType/QQRect.h>
#include <eirExe/ErrorHandler.h>

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
    void loadFrontalFace();
    void setFrontalFaceImage(const QImage &inputImage);
    void detectFrontalFaceRectangles(const QQRect region=QQRect());
    void voteFrontalFaceObjects();

private:
    bool createCascade(const ObjectType objType,
                       const VarMap &config);
    bool loadCascade(const ObjectType objType);
    bool setCascadeImage(const ObjectType objType,
                         const QImage inputImage);
    bool detectRectangles(const ObjectType objType,
                          const VarMap parameters);
    bool rectanglePolling(const ObjectType objType,
                          const VarMap parameters);

signals:
    void defaultConfigurationLoaded();
    void cascadeError(ObjectType objType, QStringList messages);
    void cascadeError(ObjectType objType, ErrorHandler::Item);
    void cascadeCreated(ObjectType objType);
    void cascadeLoaded(ObjectType objType);
    void cascadeImageSet(ObjectType objType);
    void cascadeRectangles(ObjectType objType,
                           QQRect::List rectList);
    void cascadeVotes(ObjectType objType,
                      VarMap votingResults);

private:
    Configurations mConfigurations;
    QMap<ObjectType, HaarCascade *> mTypeCascadeMap;
};

