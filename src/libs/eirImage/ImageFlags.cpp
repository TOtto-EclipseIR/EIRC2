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

    QString flagsBase("ImageBase");
    // "ImageOutputFrame ImageOutputFace ImageOutputBody ");
    QString frameBase("ImageFrameBase");
    QString faceBase("ImageFaceBase");
    QString bodyBase("ImageBodyBase");

    registerFlag(cmImageFlagsBase, flagsBase);
    registerFlag(cmImageOutputFlagsFrameBase, frameBase);
    registerFlag(cmImageOutputFlagsFaceBase, faceBase);
    registerFlag(cmImageOutputFlagsBodyBase, bodyBase);

    registerFlag(cmImageFlagsBase+QImage::Format_Mono,
                 "ImageQFormatMono");
    registerFlag(cmImageFlagsBase+QImage::Format_ARGB32,
                 "ImageQFormatARGB32");
    registerFlag(cmImageFlagsBase+QImage::Format_Grayscale8,
                 "ImageQFormatGrey8");
    registerFlag(cmImageFlagsBase+QImage::Format_Grayscale16,
                 "ImageQFormatGrey16");
    registerFlag(cmImageFlagsBase+QImage::Format_Indexed8,
                 "ImageQFormatIndexed8");
    registerFlag(cmImageFlagsBase+QImage::Format_RGB32,
                 "ImageQFormatFRGB32");
    registerFlag(cmImageFlagsBase+QImage::Format_ARGB32_Premultiplied,
                 "ImageQFormatARGB32Pre");
    registerFlag(cmImageFlagsBase+QImage::Format_RGBX64,
                 "ImageQFormatRGBF64");
    registerFlag(cmImageFlagsBase+QImage::Format_RGBA64,
                 "ImageQFormatRGBA64");
    TODO(rest of QImage::Format)

    registerFlag(cmImageQFormatFlagsBase, QString("ImageOutputFlagsFrameBase"));
    registerFlag("ImageOutputCapture");
    registerFlag("ImageOutputInput");
    registerFlag("ImageOutputInputGrey");
    registerFlag("DetectMarkedFrame");
    NEEDDO(more & more);
}
