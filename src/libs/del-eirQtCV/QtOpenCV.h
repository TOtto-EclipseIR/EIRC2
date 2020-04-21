#pragma once
#include "eirQtCV.h"

#include <QObject>

#include <QMap>

//#include <opencv2/opencv.hpp>
//#include <opencv2/objdetect.hpp>

#include <eirBase/ErrorHandler.h>
#include <eirBase/Uid.h>
#include <eirType/QQRect.h>

//#include "del-HaarCascade.h"


class EIRQTCV_EXPORT QtOpenCV : public QObject
{
    Q_OBJECT
public:

public:
    explicit QtOpenCV(QObject *parent = nullptr);

private slots:
    void initOpenCV();

private:

signals:

private:
    static eirQtCV smLib;

};

