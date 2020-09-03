#include "ObjDetPak.h"

#include <eirType/Milliseconds.h>
#include <eirXfr/Debug.h>

ObjDetPak::ObjDetPak()
    : ValuePak(Id(Milliseconds::current()))
{
    TRACEFN;
}

ObjDetPak::ObjDetPak(const QFileInfo &fileInfo, const bool load)
    : ValuePak(Id(Milliseconds::current()))
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

void ObjDetPak::setInputBytes(const QByteArray &bytes)
{

    MUSTUSE(bytes);

}

void ObjDetPak::setImage(const ObjDetPak::ImageIndex iix,
                         const MultiName &valueName,
                         const QQImage &image)
{
    TRACEQFI << iix << image;
    ValuePak::set(iix, Value(valueName, image));
}

void ObjDetPak::loadInputFile(const QFileInfo &fileInfo)
{
    MUSTUSE(fileInfo);
}
