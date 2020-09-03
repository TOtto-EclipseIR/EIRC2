#include "ObjDetPak.h"

#include <eirXfr/Debug.h>

ObjDetPak::ObjDetPak()
{

}

ObjDetPak::ObjDetPak(const QFileInfo &fileInfo, const bool load)
{
    TRACEQFI << fileInfo << load;
    if (load)
        loadInputFile(fileInfo);
    else
        setInputFileInfo(fileInfo);
}

QFileInfo ObjDetPak::inputFileInfo() const
{

    MUSTRTN(QFileInfo());
}

void ObjDetPak::setInputFileInfo(const QFileInfo &fileInfo)
{

    MUSTUSE(fileInfo);
}

void ObjDetPak::loadInputFile(const QFileInfo &fileInfo)
{
    MUSTUSE(fileInfo);
}
