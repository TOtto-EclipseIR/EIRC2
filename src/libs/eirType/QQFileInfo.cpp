// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#include "QQFileInfo.h"

QQFileInfo::QQFileInfo() {;}

QQFileInfo::QQFileInfo(const QFileInfo &other)
    : QFileInfo(other), mIsNull(false) {;}

bool QQFileInfo::isNull() const
{
    return mIsNull;
}
/*
QQFileInfo::operator QFileInfo() const
{
    return QFileInfo(*this);
}
*/

