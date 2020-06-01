//! \file ImageFlags.cpp
#include "ImageFlags.h"

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
    if (once) return;                           /* /========\ */
    once=true;

    QString flagsBase("ImageBase ImageFrame ImageFace"
                      "ImageBody ImageMarked ImageINDI");
    QString frameBase("ImageFrameBase");
    QString faceBase("ImageFaceBase");
    QString bodyBase("ImageBodyBase");

    registerFlags(cmImageFlagsBase, flagsBase);
    registerFlags(cmImageFlagsFrameBase, frameBase);
    registerFlags(cmImageFlagsFaceBase, faceBase);
    registerFlags(cmImageFlagsBodyBase, bodyBase);
}
