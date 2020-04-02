#include "QtOpenCV.h"

#include <QTimer>

#include <eirBase/Debug.h>

#include "HaarCascade.h"

QtOpenCV::QtOpenCV(QObject *parent) : QObject(parent)
{
    TRACEFN
    setObjectName("QtOpenCV");
    QTimer::singleShot(5000, this, &QtOpenCV::tryLoad);
}

void QtOpenCV::tryLoad()
{
    TRACEFN
    HaarCascade hc;
    hc.load(QFileInfo("gigglesnorf.xml"));
}
