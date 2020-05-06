#include "FileInfoQueue.h"

#include <eirBase/Debug.h>

FileInfoQueue::FileInfoQueue(QObject *parent)
    : QObject(parent)
{
    TRACEFN
    setObjectName("FileInfoQueue");
    CONNECT(this, &FileInfoQueue::incomingAdded,
            this, &FileInfoQueue::processIncoming);
}

int FileInfoQueue::incomingCount() const
{
    return mIncomingQueue.size();
}

bool FileInfoQueue::isIncomingEmpty() const
{
    return ! incomingCount();
}

int FileInfoQueue::pendingCount() const
{
    return mPendingQueue.size();
}

bool FileInfoQueue::isPendingEmpty() const
{
    return ! pendingCount();
}

void FileInfoQueue::clearInput()
{
    TRACEFN
    NEEDDO(it);
}

void FileInfoQueue::setMaxPending(const int max)
{
    TRACEFN
    NEEDDO(it);
    NEEDUSE(max)
}

void FileInfoQueue::cancelPending()
{
    TRACEFN
    NEEDDO(it);
}

void FileInfoQueue::append(const QFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    if ( ! fileInfo.exists())           return;
    if ( ! fileInfo.isWritable())       return;

    NEEDDO(more);

    mIncomingQueue.enqueue(fileInfo);
    EMIT(incomingAdded(fileInfo));
}

void FileInfoQueue::append(const QFileInfoList &fileInfoList)
{
    TRACEFN
    foreach (QFileInfo qfi, fileInfoList) append(qfi);
}

void FileInfoQueue::processIncoming()
{
    // Change mPendingFull status as necessary
    if (mPendingFull
            && pendingCount() < mMaxPending - (mMaxPending >> 2))
    {
        mPendingFull = false;
    }
    else if ( ! mPendingFull && pendingCount() > mMaxPending)
    {
        mPendingFull = true;
    }

    // Is nothing to do at this time
    if (mPendingFull || isIncomingEmpty())
    {
        QTimer::singleShot(1000, this,
                           &FileInfoQueue::processIncoming);
        return;
    }

    // More on this incoming directory?
    //if ()


    // Take next from incoming
    QFileInfo qfi = mIncomingQueue.dequeue();
    TRACE << "emit" << "incomingTaken(qfi)" << qfi;
    emit incomingTaken(qfi);
    if (qfi.isFile())
    {
        mPendingQueue.enqueue(qfi);
        return;
    }
    if (qfi.isDir())
    {
        TODO(startIterator)
    }
}
