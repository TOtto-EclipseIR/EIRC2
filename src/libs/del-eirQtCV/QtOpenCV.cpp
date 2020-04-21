#include "QtOpenCV.h"

#include <QDir>
#include <QTimer>

#include <eirBase/Debug.h>

//#include "del-HaarCascade.h"

QtOpenCV::QtOpenCV(QObject *parent) : QObject(parent)
{
    TRACEFN
    setObjectName("QtOpenCV");
    QTimer::singleShot(100, this,
        &QtOpenCV::initOpenCV);
}

void QtOpenCV::initOpenCV()
{

}
