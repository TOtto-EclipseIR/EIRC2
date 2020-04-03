#include "QtOpenCV.h"

#include <QDir>
#include <QTimer>

#include <eirBase/Debug.h>

#include "HaarCascade.h"

QtOpenCV::QtOpenCV(QObject *parent) : QObject(parent)
{
    TRACEFN
    setObjectName("QtOpenCV");
    QTimer::singleShot(100, this, &QtOpenCV::setDefaultConfiguration);
}

void QtOpenCV::setDefaultConfiguration()
{
    TRACEFN
    mConfigurations.setDefaults();
    emit defaultConfigurationLoaded();
}

void QtOpenCV::setOverideConfiguration()
{
    NEEDDO()
}

void QtOpenCV::createFrontalFace()
{
    NEEDDO()
}

void QtOpenCV::loadFrontalFace()
{
    NEEDDO()
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

