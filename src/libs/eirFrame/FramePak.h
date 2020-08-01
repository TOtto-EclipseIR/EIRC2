#pragma once

#include <eirType/VarPak.h>

#include <QFileInfo>

class FramePak : public VarPak
{
public:
    FramePak();
    FramePak(const QFileInfo &fileInfo);
    FramePak(const QFileInfo &fileInfo,
             const QByteArray &fileBytes);
    void set(const QFileInfo &fileInfo);
    void set(const QByteArray &fileBytes);
    QFileInfo fileInfo() const;
};

