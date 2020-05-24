#include "QQFileInfoList.h"

#include <eirBase/Debug.h>

#include "QQFileInfo.h"

QQFileInfoList::QQFileInfoList() {;}
QQFileInfoList::QQFileInfoList(const QFileInfoList &other) : QFileInfoList(other) {;}

void QQFileInfoList::dump(const QString &title) const
{
    DUMP << (title.isEmpty() ? "QQFileInfoList" : title);
    foreach (QQFileInfo fileInfo, *this)
    {
        DUMP << fileInfo.absoluteFilePath() << fileInfo.attributes();
    }
}

