// file: {EIRC2 repo}./src/libs/eirBase/UInt128.cpp
#include "UInt128.h"

UInt128::UInt128()
{

}

quint64 UInt128::upper() const
{
    return mUpperLowerPair.first;
}

quint64 UInt128::lower() const
{
    return mUpperLowerPair.second;
}

bool UInt128::operator ==(const UInt128 &other)
{
    return upper() == other.upper()
            && lower() == other.lower();
}
