// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#include "QQFileInfo.h"

QQFileInfo::QQFileInfo() {;}

QQFileInfo::QQFileInfo(const QString &filePathName)
    : QFileInfo(filePathName), mIsNull(false) {;}

QQFileInfo::QQFileInfo(const QFileInfo &other)
    : QFileInfo(other), mIsNull(false) {;}

bool QQFileInfo::isNull() const
{
    return mIsNull;
}

QString QQFileInfo::attributes() const
{
    if (isNull()) return "isNull ";
    QString attribString;
    if (isAbsolute())       attribString += "Absolute ";
    if (isDir())            attribString += "Dir ";
    if (isExecutable())     attribString += "Executable ";
    if (isFile())           attribString += "File ";
    if (isReadable())       attribString += "Readable ";
    if (isRoot())           attribString += "Root ";
    if (isWritable())       attribString += "Writable ";
    return attribString;
}


