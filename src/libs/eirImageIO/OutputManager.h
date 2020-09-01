// file: {repo: EIRC2}./src/libs/eirImageIO/OutputManager.h
#pragma once
#include "eirImageIO.h"

#include <QObject>

#include <QDir>
#include <QQueue>

#include <eirType/Milliseconds.h>
#include <eirExe/ConfigObject.h>
#include <eirFrame/Frame.h>
#include <eirFrame/FrameIndex.h>
#include <eirFrame/FramePak.h>

class EIRIMAGEIO_EXPORT OutputManager : public QObject
{
    Q_OBJECT
public:
    explicit OutputManager(QObject *parent = nullptr);
    explicit OutputManager(const Milliseconds timerMsec,
                           QObject *parent = nullptr);
    void setBase(const QDir &baseDir);
    int incomingQueueSize() const;
    bool incomingEmpty() const;
    FramePak firstIncoming() const;
    FramePak takeIncoming();
    bool incomingNotEmpty() const;
    ~OutputManager();

public slots:
    void configure(ConfigObject *cfgObj);
    void start(const Milliseconds msec=0);
    void pulse();
    void enqueue(FramePak incomingFP);
    void startMarkNext();
    void markNext();
    void markComplete();
    void enqueueMarked(FramePak markedFP);
    void splitMarked();

signals:
    void started(Milliseconds msec);
    void pulsed();
    void marked(FramePak markedFP);
    void incomingSize(int count);
    void incomingEmpty();

private:
    QTimer * const cmpTimer=nullptr;
    Milliseconds mTimerMsec;
    Configuration mOutputConfig;
    Configuration mMarkerConfig;
    QDir mBaseDir;
    QQueue<FramePak> mIncomingQueue;
    FramePak mCurrentFP;
    QQueue<FramePak> mMarkedQueue;
    QQueue<Frame> mWriterQueue;

};

