// file: {EIRC2 repo}./src/libs/eirQtCV/QtCVobjdetect.h
#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QHash>

#include <eirBase/SetError.h>
#include <eirBase/Uid.h>

#include "ObjectType.h"

class Detector;

class EIRQTCV_EXPORT QtCVobjdetect : public QObject, public SetError
{
    Q_OBJECT
public:
    QtCVobjdetect(QObject *parent=nullptr);
    Detector * newDetector(const ObjectType objType);

private:
    QHash<Uid, Detector *> mUidDetectorMap;
};

