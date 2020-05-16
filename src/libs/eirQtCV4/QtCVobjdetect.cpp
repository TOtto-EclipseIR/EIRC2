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

QtCVobjdetect::~QtCVobjdetect()
{
//    while ( ! mDetectorList.isEmpty())
  //      delete mDetectorList.takeFirst();
}
#if 0
Detector *QtCVobjdetect::newDetector(const ObjectType objType)
{
    TRACEQFI << objType.name();
    NEEDDO(objType switch);
    Detector * objDet = new Detector(objType, this);
    TSTALLOC(objDet)
//    mDetectorList.append(objDet);
    return objDet;
}
#endif
void QtCVobjdetect::release(Detector *det)
{
//    mDetectorList.removeAll(det);
}
