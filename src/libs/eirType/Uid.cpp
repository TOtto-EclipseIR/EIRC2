// file: {repo:EIRC2}./src/libs/eirType/Uid.cpp

#include "Uid.h"

#include <eirBase/Debug.h>

Uid::Uid(void) {;}
Uid::Uid(const QUuid quuid) { *this = quuid; }
Uid Uid::create() { return QUuid::createUuid(); }



quint64 Uid::UInt128::upper() const
{
    return mUpperLowerPair.first;
}

quint64 Uid::UInt128::lower() const
{
    return mUpperLowerPair.second;
}

bool Uid::UInt128::operator ==(const Uid::UInt128 &other)
{
    return upper() == other.upper()
            && lower() == other.lower();
}
