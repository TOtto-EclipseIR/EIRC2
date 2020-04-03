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

