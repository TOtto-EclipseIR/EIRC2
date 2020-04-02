#pragma once
#include "eirQtCV.h"

#include <QObject>

class EIRQTCV_EXPORT QtOpenCV : public QObject
{
    Q_OBJECT
public:
    explicit QtOpenCV(QObject *parent = nullptr);

signals:

};

