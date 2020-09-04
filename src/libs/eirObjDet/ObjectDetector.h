#pragma once
#include "eirObjDet.h"

#include <QObject>

#include <eirBase/Uuid.h>
#include <eirQtCV/cvCascade.h>

#include "ObjDetPak.h"

class EIROBJDET_EXPORT ObjectDetector : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetector(const cvCascade::Type type,
                            QObject *parent = nullptr);
    cvCascade * cascade();

public slots:
    void enqueue(const QFileInfo &inputFileInfo);

signals:
    void queued(ObjDetPak pak);
    void queued(int count);
    void queueNotEmpty();

private:
    cvCascade::Type cmType=cvCascade::nullType;
    cvCascade mCascade;
    ObjDetPak::Queue mInputQueue;
};

