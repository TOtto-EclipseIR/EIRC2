// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#include "QQFileInfo.h"

#include <QDir>

#include <eirBase/Debug.h>

QQFileInfo::QQFileInfo() {;}

QQFileInfo::QQFileInfo(const QString &filePathName)
    : QFileInfo(filePathName), mIsNull(false) {;}

QQFileInfo::QQFileInfo(const QFileInfo &other)
    : QFileInfo(other), mIsNull(false) {;}

bool QQFileInfo::isNull() const
{
    return mIsNull;
}

bool QQFileInfo::tryIsFile(const QIODevice::OpenMode mode) const
{
    TRACEQFI << absoluteFilePath();
    bool canOpenFile = tryIsFile(absoluteFilePath(), mode);
    TRACERTN(canOpenFile);
    return canOpenFile;
}

bool QQFileInfo::tryIsDir() const
{
    QString absolutePath = dir().absolutePath();
    TRACEQFI << absolutePath;
    bool canCdDir = tryIsDir(absolutePath);
    TRACERTN(canCdDir);
    return canCdDir;
}

QString QQFileInfo::attributes() const
{
    if (isNull()) return "isNull ";
    QString attribString;
    if (isAbsolute())       attribString += "Absolute ";
    if (tryIsDir())         attribString += "Dir ";
    if (isExecutable())     attribString += "Executable ";
    if (tryIsFile())        attribString += "File ";
    if (isReadable())       attribString += "Readable ";
    if (isRoot())           attribString += "Root ";
    if (isWritable())       attribString += "Writable ";
    return attribString;
}

QString QQFileInfo::toString() const
{
    if (tryIsDir())     return absolutePath();
    if (tryIsFile())    return absoluteFilePath();
    return fileName();
}

QString QQFileInfo::operator ()() const
{
    return toString();
}

QQFileInfo::operator QString() const
{
    return toString();
}

//static
bool QQFileInfo::tryIsFile(const QString &filePathName,
                           const QIODevice::OpenMode mode)
{
    TRACEQFI << filePathName;
    QFile file(filePathName);
    bool canOpenFile = file.open(QIODevice::ExistingOnly | mode);
    TRACERTN(canOpenFile);
    return canOpenFile;
}

//static
bool QQFileInfo::tryIsDir(const QString &pathName)
{
    TRACEQFI << pathName;
    QDir tryDir;
    bool canCdDir = tryDir.cd(pathName);
    TRACERTN(canCdDir)
    return canCdDir;
}

