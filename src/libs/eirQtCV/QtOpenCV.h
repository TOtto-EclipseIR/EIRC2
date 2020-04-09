#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QMap>

#include <eirType/QQRect.h>
#include <eirBase/ErrorHandler.h>

#include "Configurations.h"

class HaarCascade;

class EIRQTCV_EXPORT QtOpenCV : public QObject
{
    Q_OBJECT
public:
    enum ObjectType
    {
        nullObjectType = 0,
        FrontalFace,
        LeftEye,
        RightEye,
        EitherEye,
        BothEyes,
        sizenullObjectType
    };

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
    void overideConfigurationLoaded();
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

