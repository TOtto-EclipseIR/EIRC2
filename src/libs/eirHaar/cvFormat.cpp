//! \file cvFormat.cpp
#include "cvFormat.h"

cvFormat::cvFormat() {;}

int cvFormat::toInt() const
{
    return int(mType);
}

int cvFormat::operator ()() const
{
    return  toInt();
}
