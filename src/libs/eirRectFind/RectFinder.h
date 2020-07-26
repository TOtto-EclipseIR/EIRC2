#pragma once
#include "eirRectFind.h"

#include <QObject>

#include <eirType/BasicName.h>
#include <eirQtCV/cvCascade.h>

class EIRRECTFIND_EXPORT RectFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectFinder(QObject *parent = nullptr);

signals:

private:
    QMap<BasicName, cvCascade> mNameCascadeMap;
};

