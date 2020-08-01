#pragma once

#include <QDir>

class BaseOutputDir : public QDir
{
public:
    BaseOutputDir(const QString &pathName=QString());
    void setPath(const QString &path, const QString &format=QString());
};

