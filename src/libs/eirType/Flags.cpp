#include "Flags.h"

#include <eirBase/Debug.h>

Flags::Flags(const int sz, const bool iz)
{
    TRACEQFI << sz << iz;
    resize(sz, true);
    EXPECTEQ(sz, size());
    fill(iz);
    EXPECT(isAll(iz));
}

int Flags::size() const
{
    return mBits.size();
}

void Flags::resize(const int newSize, const bool truncate)
{
    if (truncate)
        for (int index = newSize; index < size(); ++index)
            remove(namePch(index));
    if (truncate || newSize > size())
        mBits.resize(newSize);
}

void Flags::fill(const bool is)
{
    mBits.fill(is);
}

bool Flags::isAll(const bool is) const
{
    bool isNot = ! is;
    for (int index = 0; index < size(); ++index)
        if (isNot == at(index)) return false;
    return true;
}

bool Flags::at(const int index) const
{
    return mBits.at(index);
}

BasicName Flags::name(const int index) const
{
    return mIndexNameDMap.at(index);
}

const char *Flags::namePch(const int index) const
{
    return name(index)().toLocal8Bit();
}
