//! \file HaarBase.h
#pragma once
#include "eirHaar.h"

#include <QDir>

#include <eirExe/FileName.h>

class EIRHAAR_EXPORT HaarBase
{
public:
    HaarBase(const QString &baseDirPath=QString());
    void set(const QString &baseDirPath);
    FileName baseFileName(const FileName &inFileName);
    QDir baseDir() const;

private:
    QString mBaseDirPath;
    QDir mBaseDir;
};

