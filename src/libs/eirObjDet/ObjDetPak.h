#pragma once

#include <QFileInfo>

#include <eirType/ValuePak.h>

class ObjDetPak : public ValuePak
{
public:
    ObjDetPak();
    ObjDetPak(const QFileInfo &fileInfo, const bool andLoad=true);
    QFileInfo inputFileInfo() const;
    void setInputFileInfo(const QFileInfo &fileInfo);
    void loadInputFile(const QFileInfo &fileInfo);
};

