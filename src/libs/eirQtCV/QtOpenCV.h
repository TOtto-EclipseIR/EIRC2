#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QMap>

#include <eirBase/ErrorHandler.h>
#include <eirBase/Uid.h>
#include <eirType/QQRect.h>

#include "Configurations.h"

class HaarCascade;

class EIRQTCV_EXPORT QtOpenCV : public QObject
{
    Q_OBJECT
public:
    enum ObjectType
    {
        nullObjectType = 0,
        FrontalFace = 0x01,
        LeftEye = 0x10,
        RightEye = 0x20,
        EitherEye = 0x40,
        BothEyes = 0x80,
        maskObjectType = 0xF1
    };
    Q_DECLARE_FLAGS(ObjectTypeList, ObjectType)

public:
    explicit QtOpenCV(QObject *parent = nullptr);
    void setObjectLoadTypes(const ObjectTypeList types);
    void startCascadeLoad();
    void processFrame(const QFileInfo qfi);
    bool setInputImage(const Uid uid,
                       const ObjectType objType,
                         const QImage inputImage,
                         const bool equalize=true);
    bool detectRectangles(const Uid uid,
                          const ObjectType objType,
                          const VarMap parameters);
    bool rectanglePolling(const Uid uid,
                          const ObjectType objType,
                          const VarMap parameters);

private slots:
    void setDefaultConfiguration();
    void setOverideConfiguration();
    void initOpenCV();
    void loadNextCascade();
    void createFrontalFace();
    void createEitherEye();
    void loadFrontalFace();
    void loadEitherEye();
    void setFrontalFaceImage(const QImage &inputImage);
    void detectFrontalFaceRectangles(
            const QQRect region=QQRect());
    void voteFrontalFaceObjects();

private:
//    Uid createCascade(const ObjectType objType, const VarMap &config);
//    bool loadCascade(const Uid uid, const ObjectType objType);
//    bool clearCascade(const ObjectTypeList, objTypeMask=maskObjectType /*default all*/);

signals:
    void defaultConfigurationLoaded();
    void overideConfigurationLoaded();
    void cascadeLoadReady();
    void cascadeError(ObjectType objType, QStringList messages);
    void cascadeError(ObjectType objType, ErrorHandler::Item);
    void cascadeCreated(ObjectType objType);
    void cascadeCleared(ObjectType objType);
    void loadingCascade(ObjectType objType);
    void cascadeLoaded(ObjectType objType);
    void cascadeLoadFinished();
    void cascadeImageSet(const Uid uid,
                         ObjectType objType);
    void cascadeRectangles(const Uid uid,
                           ObjectType objType,
                           QQRect::List rectList);
    void cascadeVotes(const Uid uid,
                      ObjectType objType,
                      VarMap votingResults);

private:
    Configurations mConfigurations;
    QHash<Uid, HaarCascade *> mTypeCascadeMap;
    QtOpenCV::ObjectTypeList mObjectTypes=0;
    QtOpenCV::ObjectTypeList mTypesPending=0;


};

Q_DECLARE_OPERATORS_FOR_FLAGS(QtOpenCV::ObjectTypeList)
