// file:{EIRC2 repo}./src/libs/eirImage/ImageFlags.cpp
//! \file ImageFlags.cpp
#include "ImageFlags.h"

#include <QImage>

#include <eirBase/Debug.h>

ImageFlags::ImageFlags()
{
    TRACEFN
    ctorOnce();
}

void ImageFlags::ctorOnce()
{
    TRACEFN
    static bool once=false;
    if (once) return;                                   /* /========\ */
    once=true;

    QString flagsBase("ImageBase ImageOutputFrame ImageOutputFace "
                      "ImageOutputBody ");
    QString frameBase("ImageFrameBase");
    QString faceBase("ImageFaceBase");
    QString bodyBase("ImageBodyBase");

    registerFlags(cmImageFlagsBase, flagsBase);
    registerFlag(cmImageFlagsBase+QImage::Format_Mono,
                 name(cmImageFlagsBase) + "QFormatMono");
    registerFlag(cmImageFlagsBase+QImage::Format_ARGB32,
                 name(cmImageFlagsBase) + "QFormatARGB32");
    registerFlag(cmImageFlagsBase+QImage::Format_Grayscale8,
                 name(cmImageFlagsBase) + "QFormatGrey8");
    registerFlag(cmImageFlagsBase+QImage::Format_Grayscale16,
                 name(cmImageFlagsBase) + "QFormatGrey16");
    registerFlag(cmImageFlagsBase+QImage::Format_Indexed8,
                 name(cmImageFlagsBase) + "QFormatIndexed8");
    registerFlag(cmImageFlagsBase+QImage::Format_RGB32,
                 name(cmImageFlagsBase) + "QFormatFRGB32");
    registerFlag(cmImageFlagsBase+QImage::Format_ARGB32_Premultiplied,
                 name(cmImageFlagsBase) + "QFormatARGB32Pre");
    registerFlag(cmImageFlagsBase+QImage::Format_RGBX64,
                 name(cmImageFlagsBase) + "QFormatRGBF64");
    registerFlag(cmImageFlagsBase+QImage::Format_RGBA64,
                 name(cmImageFlagsBase) + "QFormatRGBA64");
    TODO(rest of QImage::Format)

    registerFlags(cmImageOutputFlagsFrameBase, frameBase);
    registerFlags(cmImageOutputFlagsFaceBase, faceBase);
    registerFlags(cmImageOutputFlagsBodyBase, bodyBase);
}
