// file: {EIRC2 repo}./src/libs/eirQtCV/QtCVobjdetect.h
#pragma once
#include "eirQtCV4.h"

#include <QObject>

#include <QList>

#include <eirBase/SetError.h>
//#include <eirBase/Uid.h>

#include "ObjectType.h"

class Detector;

class EIRQTCV4_EXPORT QtCVobjdetect
        : public QObject, public SetError
{
    Q_OBJECT
public:
    QtCVobjdetect(QObject *parent=nullptr);
    ~QtCVobjdetect();
    Detector * newDetector(const ObjectType objType);
    void release(Detector * det);

private:
//    QList<Detector *> mDetectorList;
};

