// file:{EIRC2 repo}./src/libs/eirImage/ImagePakWriterQueue.cpp
//! \file ImagePakWriterQueue.cpp
#include "ImagePakWriterQueue.h"

#include <QDir>
#include <QString>

#include <eirBase/Debug.h>

ImagePakWriterQueue::ImagePakWriterQueue(QObject *parent)
    : QObject(parent)
{
    TRACEQFI << (parent ? parent->objectName() : "{NULL parent}");
    CONNECT(this, SIGNAL(enqueued(QUuid uid, MultiName name, ImagePak pak)),
            this, SLOT(onEnqueued(QUuid uid, MultiName name, ImagePak pak)));
    CONNECT(this, SIGNAL(dequeued(QUuid uid, MultiName name, ImagePak pak)),
            this, SLOT(onDequeued(QUuid uid, MultiName name, ImagePak pak)));
    EMIT(ready());
    EMIT(changed(0));
}

void ImagePakWriterQueue::configureOutput(const Configuration outputConfig)
{
    TRACEFN
    mConfiguration = outputConfig;
    setupDirs();
}

ImagePak ImagePakWriterQueue::takeDequePak()
{
    TRACEFN
    NEEDDO(it);;
    return ImagePak();
}

ImagePak ImagePakWriterQueue::peekDequePak() const
{
    TRACEFN
    NEEDDO(it);;
    return ImagePak();
}

ImagePak ImagePakWriterQueue::lastDequeuedPak() const
{
    TRACEFN
    NEEDDO(it);;
    return ImagePak();
}

ImagePakWriterQueue::ImageFileItem ImagePakWriterQueue::peekDequeFile() const
{
    TRACEFN
    return ImageFileItem();
}

ImagePakWriterQueue::ImageFileItem ImagePakWriterQueue::takeDequeFile()
{
    TRACEFN
    return ImageFileItem();
}

void ImagePakWriterQueue::setupDirs()
{
    TRACEFN;
    QString baseDirName = mConfiguration
                .value("BaseDir").currentVari().toString();
    Configuration dirsConfig = mConfiguration.extract("Dirs");
    DUMPVAL(baseDirName);
    dirsConfig.dump();

    QDir baseDir(baseDirName);
    WEXPECT(baseDir.mkpath("."));
    MultiName::List dirsKeys;
    foreach (Var dirVar, dirsConfig.values())           /* /-----\ */
    {
        if (dirVar.currentVari().isNull()) continue;    /* \-----/ */
        QString dirName = dirVar.value().toString();
        QDir outputDir = baseDir;
        WEXPECT(outputDir.mkpath(dirName));
        WEXPECT(outputDir.cd(dirName));

        DirItem item(dirVar.name().lastSegment());
        item.set(outputDir);
        TODO(flags);
//        ImageFlags flags;
  //      flags.set(TBD);
        TODO(more?);
        WEXPECTNOT(mNameDirItemMap
                    .contains(item.name()));
        mNameDirItemMap.insert(
                    dirVar.name().lastSegment(), item);
    }
}

void ImagePakWriterQueue::enqueue(ImagePak pak)
{
    TRACEQFI << pak.id().name()();
    NEEDDO(it);;
}

void ImagePakWriterQueue::dequeue()
{
    TRACEFN
    NEEDDO(it);;
}

void ImagePakWriterQueue::onChanged(int size)
{
    TRACEFN
    NEEDDO(it);; NEEDUSE(size);
}

void ImagePakWriterQueue::onEnqueued(QUuid uid, MultiName name, ImagePak pak)
{
    TRACEQFI << pak.id().name()();
    NEEDDO(it);; NEEDUSE(uid); NEEDUSE(name); NEEDUSE(pak);
}

void ImagePakWriterQueue::onDequeued(QUuid uid, MultiName name, ImagePak pak)
{
    TRACEQFI << pak.id().name()();
    NEEDDO(it);; NEEDUSE(uid); NEEDUSE(name); NEEDUSE(pak);
}

void ImagePakWriterQueue::enqueueFile(ImagePakWriterQueue::ImageFileItem item)
{
    TRACEQFI << item.first; // << which mark and output image-bitflag?
    NEEDDO(it);; NEEDUSE(item);
}

void ImagePakWriterQueue::dequeueFile()
{
    TRACEQFI << peekDequeFile().first;
    NEEDDO(it);;
}


ImagePakWriterQueue::DirItem::DirItem(const BasicName &name)
    : mNameKey(name)
{

}

BasicName ImagePakWriterQueue::DirItem::name() const
{
    return mNameKey;
}

void ImagePakWriterQueue::DirItem::set(const QDir dir)
{
    mDir = dir;
}
