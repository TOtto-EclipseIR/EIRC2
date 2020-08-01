#include "FramePak.h"

FramePak::FramePak()
{

}

FramePak::FramePak(const QFileInfo &fileInfo)
{
    set(fileInfo);
}

FramePak::FramePak(const QFileInfo &fileInfo,
                   const QByteArray &fileBytes)
{
    set(fileInfo);
    set(fileBytes);
}

void FramePak::set(const QFileInfo &fileInfo)
{
    setValue(QVariant(fileInfo.absoluteFilePath()));
}

void FramePak::set(const QByteArray &fileBytes)
{
    VarPak::set(fileBytes);
}

QFileInfo FramePak::fileInfo() const
{
    return QFileInfo(id().data().toString());
}

