// file: {EIRC2 repo)./src/libs/eirType/QQFileInfoList.h
#pragma once
#include "eirType.h"

#include <QFileInfoList>
#include <QString>

class EIRTYPE_EXPORT QQFileInfoList : public QFileInfoList
{
public:
    QQFileInfoList();
    QQFileInfoList(const QFileInfoList &other);
    void dump(const QString &title=QString()) const;
};

