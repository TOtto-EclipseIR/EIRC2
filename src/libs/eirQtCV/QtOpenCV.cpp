#include "QtOpenCV.h"

#include <QDir>
#include <QTimer>

#include <eirBase/Debug.h>

#include "HaarCascade.h"

QtOpenCV::QtOpenCV(QObject *parent) : QObject(parent)
{
    TRACEFN
    setObjectName("QtOpenCV");
    CONNECT(this, &QtOpenCV::defaultConfigurationLoaded,
            this, &QtOpenCV::setOverideConfiguration);
    CONNECT(this, &QtOpenCV::cascadeLoadReady,
            this, &QtOpenCV::loadNextCascade);
    QTimer::singleShot(100, this,
        &QtOpenCV::setDefaultConfiguration);
}

void QtOpenCV::setObjectLoadTypes(const ObjectTypeList types)
{
    //clearCascade(/*all*/);
    mObjectTypes = mTypesPending = types;
}

void QtOpenCV::startCascadeLoad()
{
    TRACEFN
    emit cascadeLoadReady();
}

void QtOpenCV::setDefaultConfiguration()
{
    TRACEFN
    mConfigurations.setDefaults();
    emit defaultConfigurationLoaded();
}

void QtOpenCV::setOverideConfiguration()
{
    TRACEFN
    mConfigurations.setOveride();
    emit overideConfigurationLoaded();
}

void QtOpenCV::initOpenCV()
{

}

void QtOpenCV::createFrontalFace()
{
    TRACEFN
    //createCascade(ObjectType::FrontalFace, VarMap());
    NEEDDO()
}

void QtOpenCV::createEitherEye()
{

}

void QtOpenCV::loadFrontalFace()
{
    TRACEFN
    emit loadingCascade(FrontalFace);
//    if (loadCascade(FrontalFace))
        emit cascadeLoaded(FrontalFace);
}

void QtOpenCV::loadEitherEye()
{
    TRACEFN
    emit loadingCascade(EitherEye);
    NEEDDO()
    emit cascadeLoaded(EitherEye);
}

void QtOpenCV::setFrontalFaceImage(const QImage &inputImage)
{
    NEEDUSE(inputImage)
    NEEDDO()
}

void QtOpenCV::detectFrontalFaceRectangles(const QQRect region)
{
    NEEDUSE(region)
    NEEDDO()
}

void QtOpenCV::voteFrontalFaceObjects()
{
    NEEDDO()
}
/*
Uid QtOpenCV::createCascade(const QtOpenCV::ObjectType objType, const VarMap &config)
{

}
*/
void QtOpenCV::loadNextCascade()
{
    TRACEQFI << mTypesPending;
    if (0 ==mTypesPending)
    {
        emit cascadeLoadFinished();
    }
    else if (mTypesPending.testFlag(FrontalFace))
    {
        createFrontalFace();
        loadFrontalFace();
        mTypesPending.setFlag(FrontalFace, false);
    }
    else if (mTypesPending.testFlag(EitherEye))
    {
        createEitherEye();
        loadEitherEye();
        mTypesPending.setFlag(EitherEye, false);
    }
    TODO(Finish ObjectTypes)
            QTimer::singleShot(1000, this,
                    &QtOpenCV::loadNextCascade);
}
/*
bool QtOpenCV::createCascade(const QtOpenCV::ObjectType objType,
                             const VarMap &config)
{
    TRACEQFI << objType;
    HaarCascade * haar = new HaarCascade(objType, config);
    TSTALLOC(haar);
    mTypeCascadeMap.insert(haar->uid(), haar);
    emit cascadeCleared(objType);
    return true;
}
*//*
bool QtOpenCV::loadCascade(const QtOpenCV::ObjectType objType)
{
    TRACEQFI << objType;
    HaarCascade * haar = mTypeCascadeMap.value(objType);
    TSTALLOC(haar);
    return haar->load(QFileInfo());
}
*//*
bool QtOpenCV::clearCascade(const ObjectTypeList objTypeMask)
{
    TRACEQFI << objTypeMask;
    if (objTypeMask.testFlag(FrontalFace)
            && mTypeCascadeMap.contains(FrontalFace))
    {
        mTypeCascadeMap.value(FrontalFace)->destroy();
        mTypeCascadeMap.remove(FrontalFace);
    }
    return true;
}
*//*
bool QtOpenCV::setInputImage(
        const QtOpenCV::ObjectType objType,
        const QImage inputImage,
        const bool equalize)
{
    TRACEQFI << objType << inputImage << equalize;
}
*/
