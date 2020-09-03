#include "ObjDetPak.h"

#include <eirType/Milliseconds.h>
#include <eirType/QQFile.h>
#include <eirXfr/Debug.h>

ObjDetPak::ObjDetPak()
    : ValuePak(Id(Milliseconds::current()))
{
    TRACEFN;
}

ObjDetPak::ObjDetPak(const QQFileInfo &fileInfo, const bool load)
    : ValuePak(Id(Milliseconds::current()))
{
    TRACEQFI << fileInfo << load;
    if (load)
        loadInputImage(fileInfo);
    else
        setInputFileInfo(fileInfo);
}

ObjDetPak::ObjDetPak(const QByteArray &bytes, const bool load)
{
    TRACEQFI << bytes << load;
    if (load)
        loadInputImage(bytes);
    else
        setInputBytes(bytes);
}

QQFileInfo ObjDetPak::inputImageFileInfo() const
{
    TRACEFN;
    return ValuePak::at("InputImage/FileInfo");
}

QByteArray ObjDetPak::inputImageBytes() const
{
    TRACEFN;
    return ValuePak::bytes();
}

void ObjDetPak::setInputFileInfo(const QQFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    ValuePak::set("InputImage/FileInfo", fileInfo.toVariant());
}

void ObjDetPak::setInputBytes(const QByteArray &bytes)
{
    TRACEQFI << bytes;
    ValuePak::set(bytes);
    loadInputImage();
}

void ObjDetPak::loadInputImage(const QQFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    setInputFileInfo(fileInfo);
    loadInputImage();
}

void ObjDetPak::loadInputImage(const QByteArray &bytes)
{
    TRACEQFI << bytes;
    setInputBytes(bytes);
    loadInputImage();
}

void ObjDetPak::loadInputImage()
{
    TRACEFN;
    QQFileInfo imageFileInfo = inputImageFileInfo();
    QByteArray imageBytes = inputImageBytes();
    DUMPVAL(imageFileInfo);
    DUMPVAL(imageBytes);
    if (imageBytes.isEmpty())
    {
        EXPECT(imageFileInfo.isReadable() && imageFileInfo.isFile());
        imageBytes = QQFile::readAll(imageFileInfo);
        DUMPVAL(imageBytes);
        EXPECTNOT(imageBytes.isEmpty());
        if (imageBytes.isEmpty()) return;                   /* /========\ */
        ValuePak::set(imageBytes);
    }
    QQImage inputImage = QQImage::fromData(imageBytes);
    DUMPVAL(inputImage);
    EXPECTNOT(inputImage.isNull());
    if (inputImage.isNull()) return;                        /* /========\ */
    setImage(InputImage, inputImage);
    TRACERTV();
}

/* ======== private ======================================= */

void ObjDetPak::setImage(const ObjDetPak::ImageIndex iix,
                         const QQImage &image)
{
    TRACEQFI << iix << image;
    ValuePak::set(iix, image);
}
