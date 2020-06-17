// file:{EIRC2 repo}./src/libs/eirImage/ImagePakWriterQueue.h
#pragma once
#include "eirImage.h"

#include <QObject>

#include <QByteArray>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QPair>
#include <QQueue>
#include <QUuid>

#include <eirExe/ConfigObject.h>

#include "ImageFlags.h"
#include "ImagePak.h"

class EIRIMAGE_EXPORT ImagePakWriterQueue : public QObject
{
    Q_OBJECT
protected:
    typedef QPair<QFileInfo, QImage> ImageFileItem;

    class DirItem
    {
    public:
        DirItem(const BasicName &name);
        BasicName name() const;
        void set(const QDir dir);

    private:
        BasicName mNameKey;
//        ImageFlags mFlags;
        QDir mDir;
        Configuration mDirConfig;
        Configuration mMarkerConfig;
    }; // DirItem;

public:
    explicit ImagePakWriterQueue(QObject *parent = nullptr);
    void configureOutput(const Configuration outputConfig);
    ImagePak peekDequePak() const;
    ImagePak takeDequePak();
    ImagePak lastDequeuedPak() const;
    ImageFileItem peekDequeFile() const;
    ImageFileItem takeDequeFile();

public slots:
    void setupDirs();
    void enqueue(ImagePak pak);
    void dequeue();

protected slots:
    void onChanged(int size);
    void onEnqueued(QUuid uid, MultiName name, ImagePak pak);
    void onDequeued(QUuid uid, MultiName name, ImagePak pak);
    void enqueueFile(ImageFileItem item);
    void dequeueFile();

signals:
    void changed();
    void changed(int size);
    void enqueued();
    void enqueued(QUuid uid, MultiName name, ImagePak pak);
    void enqueued(MultiName name);
    void enqueued(ImagePak pak);
    void enqueued(QUuid uid);
    void dequeued();
    void dequeued(QUuid uid, MultiName name, ImagePak pak);
    void dequeued(ImagePak pak);
    void dequeued(MultiName name);
    void dequeued(QUuid uid);
    void ready();
    void empty();
    void fileNotEmpty();
    void fileEnqueued(QFileInfo fi);
    void fileDequeued(QFileInfo fi);
    void FileEmpty();
    void notEmpty();

private:
    Configuration mConfiguration;
    QMap<BasicName, DirItem> mNameDirItemMap;
    QQueue<ImagePak> mPakQueue;
    QQueue<ImageFileItem> mFileQueue;
    ImagePak mLastDequeuedPak;
    QFileInfo mLastDequeuedFI;
    QImage mLastDequeuedImage;
    QByteArray mLastDequeuedBytes;
};

