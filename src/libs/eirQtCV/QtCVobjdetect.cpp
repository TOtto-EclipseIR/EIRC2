// file: {EIRC2 repo}./src/lib/eirQtCV/QtCVobjdetect.cpp
#include "QtCVobjdetect.h"

#include <eirBase/Debug.h>

#include "Detector.h"

QtCVobjdetect::QtCVobjdetect(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("QtCVobjdetect");
}

Detector *QtCVobjdetect::newDetector(const ObjectType objType)
{
    TRACEQFI << objType.name();
    Detector * objDet = new Detector(objType, this);
    TSTALLOC(objDet)
    mUidDetectorMap.insert(objDet->uid(), objDet);
    return objDet;
}
