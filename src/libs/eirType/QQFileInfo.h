// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#pragma once
#include "eirType.h"

#include <QFileInfo>

#include <QList>


class EIRTYPE_EXPORT QQFileInfo : public QFileInfo
{
public:
    typedef QList<QQFileInfo> List;
public:
    QQFileInfo();
    QQFileInfo(const QString &filePathName);
    QQFileInfo(const QFileInfo & other);
    bool isNull() const;
    QString attributes() const;

private:
    bool mIsNull=true;
};

