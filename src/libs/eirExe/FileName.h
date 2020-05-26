// file: {EIRC2 Repo}./src/libs/eirExe/FileName.h
#pragma once
#include "eirExe.h"

#include <QString>

class EIREXE_EXPORT FileName
{
public:
    FileName(const QString &qstr=QString());
    void set(const QString &qstr);
    QString toString() const;
    operator QString () const;
    QString operator ()() const;

private:
    QString mQString;
};

