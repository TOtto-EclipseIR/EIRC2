//! \file HaarBase.cpp
#include "HaarBase.h"

#include <QFileInfo>

#include <eirBase/Debug.h>

HaarBase::HaarBase(const QString &baseDirPath)
{
    TRACEQFI << baseDirPath;
    set(baseDirPath);
}

void HaarBase::set(const QString &baseDirPath)
{
    TRACEQFI << baseDirPath;
    mBaseDirPath = baseDirPath;
    mBaseDir = QDir(baseDirPath);
    TRACE << mBaseDir;
}

FileName HaarBase::baseFileName(const FileName &inFileName)
{
    TRACEQFI << inFileName;
    QFileInfo qfi(mBaseDir, inFileName);
    FileName outFileName = qfi.absoluteFilePath();
    TRACE << outFileName;
    return outFileName;
}

QDir HaarBase::baseDir() const
{
    return mBaseDir;
}
