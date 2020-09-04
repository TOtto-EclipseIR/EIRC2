#pragma once
#include "eirObjDet.h"

#include <QObject>

class QTimer;

#include <eirBase/Uuid.h>
#include <eirType/Milliseconds.h>
#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>

#include "ObjDetPak.h"

class EIROBJDET_EXPORT ObjectDetector : public QObject
{
    Q_OBJECT
public:
    explicit ObjectDetector(const cvCascade::Type type,
                            ConfigObject * cfgObj,
                            QObject *parent = nullptr);
    cvCascade * cascade();

public slots:
    void start(const Milliseconds pulseMsec=0);
    void enqueue(const QFileInfo &inputFileInfo);
    void dequeue(const int count=1);
    void release(const Uuid uuid);
    void stop();

signals:
    // setup
    void ctored();
    void initialized();
    void configured();
    void ready();
    void started();
    void stopped();

    // running
    void pakInserted(int count);
    void inputQueued(Uuid uuid);
    void inputQueued(int count);
    void inputQueueNotEmpty();
    void dequeueEmpty();
    void dequeueNotEmpty();
    void dequeued(Uuid uuid);
    void dequeued(int count);

    // internal TBD


private slots:
    // setup
    void initialize();
    void configure();
    void readyStart();

    // running
    void pulse();
    void loadInput(const Uuid uuid);
    void findRects(const Uuid uuid);
    void groupRects(const Uuid uuid);
    void removeReleased(const Uuid uuid);

private:
    cvCascade::Type cmType=cvCascade::nullType;
    cvCascade mCascade;
    ConfigObject  * const cmpConfig=nullptr;
    QTimer  * const cmpTimer=nullptr;
    Configuration mObjDetConfig;
    ObjDetPak::UuidMap mPakMap;
    Uuid::Queue mInputQueue;
    Uuid::Queue mFinderQueue;
    Uuid::Queue mGrouperQueue;
    Uuid::Queue mProcessedQueue;
    Uuid::Queue mReleasedQueue;
};

