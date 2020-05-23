// file: {repo: EIRC2}./src/libs/eirType/QQFileInfo.h
#pragma once
#include "eirType.h"

#include <QFileInfo>


class EIRTYPE_EXPORT QQFileInfo : public QFileInfo
{
public:
    QQFileInfo();
    QQFileInfo(const QFileInfo & other);
    bool isNull() const;
//    operator QFileInfo() const;

private:
    bool mIsNull=true;
};

