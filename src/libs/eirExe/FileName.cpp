// file: {EIRC2 Repo}./src/libs/eirExe/FileName.cpp
#include "FileName.h"

#include <eirBase/Debug.h>

FileName::FileName(const QString &qstr)
    : mQString(qstr)
{
    TRACEQFI << qstr;
}

void FileName::set(const QString &qstr)
{
    mQString = qstr;
}

QString FileName::toString() const
{
    return mQString;
}

QString FileName::operator ()() const
{
    return toString();
}

FileName::operator QString() const
{
    return toString();
}
