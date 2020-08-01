// file: {repo: EIRC2}./src/libs/eirImageIO/BaseOutputDir.h
#pragma once
#include "eirImageIO.h"

#include <QDir>

class EIRIMAGEIO_EXPORT BaseOutputDir : public QDir
{
public:
    BaseOutputDir(const QString &pathName=QString());
    void setPath(const QString &path, const QString &format=QString());
};

