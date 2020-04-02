#include "QtOpenCV.h"

#include <eirBase/Debug.h>

#include "HaarCascade.h"

QtOpenCV::QtOpenCV(QObject *parent) : QObject(parent)
{
    HaarCascade hc;
    hc.load(QFileInfo("gigglesnorf.xml"));
}
