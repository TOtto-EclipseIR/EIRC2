#include "BaseOutputDir.h"

#include <eirExe/ApplicationHelper.h>

BaseOutputDir::BaseOutputDir(const QString &pathName)
{
    setPath(pathName);
}

void BaseOutputDir::setPath(const QString &path,
                            const QString &format)
{
    QString dirPath = path;
    dirPath.replace("@", ApplicationHelper::baseDateTime()
        .toString(format.isEmpty() ? "DyyyyMMdd-Thhmmss" : format));
    QDir::setPath(dirPath);
}
