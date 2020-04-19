#include "Detector.h"

#include <eirBase/Debug.h>


Detector::Detector(const ObjectType objType, QObject *parent)
    : QObject(parent)
    , cmUid(Uid::create())
    , cmObjectType(objType)
{
    setObjectName("Detector:" + objType.name());
}

Uid Detector::uid() const
{
    return cmUid;
}

ObjectType Detector::objectType() const
{
    return cmObjectType;
}
