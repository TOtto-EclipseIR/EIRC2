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

ObjDetPak::ObjDetPak(const QQByteArray &bytes, const bool load)
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

QQByteArray ObjDetPak::inputImageBytes() const
{
    TRACEFN;
    return ValuePak::bytes();
}

void ObjDetPak::setInputFileInfo(const QQFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    ValuePak::set("InputImage/FileInfo", fileInfo.toVariant());
}

void ObjDetPak::setInputBytes(const QQByteArray &bytes)
{
    TRACEQFI << bytes.traceString();
    ValuePak::set(bytes);
    loadInputImage();
}

void ObjDetPak::loadInputImage(const QQFileInfo &fileInfo)
{
    TRACEQFI << fileInfo;
    setInputFileInfo(fileInfo);
    loadInputImage();
}

void ObjDetPak::loadInputImage(const QQByteArray &bytes)
{
    TRACEQFI << bytes.traceString();
    setInputBytes(bytes);
    loadInputImage();
}

void ObjDetPak::loadInputImage()
{
    TRACEFN;
    QQFileInfo imageFileInfo = inputImageFileInfo();
    QQByteArray imageBytes = inputImageBytes();
    DUMPVAL(imageFileInfo);
    DUMP << "imageBytes = " << imageBytes.traceString();
    if (imageBytes.isEmpty())
    {
        EXPECT(imageFileInfo.isReadable() && imageFileInfo.isFile());
        imageBytes = QQFile::readAll(imageFileInfo);
        DUMP << "imageBytes = " << imageBytes.traceString();
        EXPECTNOT(imageBytes.isEmpty());
        if (imageBytes.isEmpty()) return;                   /* /========\ */
        ValuePak::set(imageBytes);
    }
    QQImage inputImage = QQImage::fromData(imageBytes);
    DUMP << inputImage;
    EXPECTNOT(inputImage.isNull());
    if (inputImage.isNull()) return;                        /* /========\ */
    setImage(InputImageIndex, inputImage);
    TRACERTV();
}

/* ======== private ======================================= */

void ObjDetPak::setImage(const ObjDetPak::ImageIndex iix,
                         const QQImage &image)
{
    TRACEQFI << iix << image;
    ValuePak::set(iix, image);
}
