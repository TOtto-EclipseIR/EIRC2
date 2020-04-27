// file: {EIRC2 repo}./src/libs/eirPixelImage/qiFormat.h
#pragma once
#include "eirPixelImage.h"

#include <eirType/Enumeration.h>

#include <QImage>


#define QIFORMAT_ENUM(NV) \
    NV(null, = 0)  \
    NV(Invalid,         = QImage::Format_Invalid)       /*  0 */ \
    NV(Mono,            = QImage::Format_Mono)          /*  1 */ \
    NV(MonoLSB,            = QImage::Format_MonoLSB)          /*  2 */ \
    NV(Indexed8,            = QImage::Format_Indexed8)          /*  3 */ \
    NV(RGB32,            = QImage::Format_RGB32)          /*  4 */ \
    NV(ARGB32,            = QImage::Format_ARGB32)          /*  5 */ \
    NV(ARGB32_Premultiplied,            = QImage::Format_ARGB32_Premultiplied)          /*  6 */ \
    NV(RGB16,            = QImage::Format_RGB16)          /*  7 */ \
    NV(ARGB8565_Premultiplied,            = QImage::Format_ARGB8565_Premultiplied)          /*  8 */ \
    NV(RGB666,            = QImage::Format_RGB666)          /*  9 */ \
    NV(ARGB6666_Premultiplied,            = QImage::Format_ARGB6666_Premultiplied)          /* 100 */ \
    NV(RGB555,            = QImage::Format_RGB555)          /* 11 */ \
    NV(ARGB8555_Premultiplied,            = QImage::Format_ARGB8555_Premultiplied)          /* 12 */ \
    NV(RGB888,            = QImage::Format_RGB888)          /* 13 */ \
    NV(RGB444,            = QImage::Format_RGB444)          /* 14 */ \
    NV(ARGB4444_Premultiplied,            = QImage::Format_ARGB4444_Premultiplied)          /* 15 */ \
    NV(RGBX8888,            = QImage::Format_RGBX8888)          /* 16 */ \
    NV(RGBA8888,            = QImage::Format_RGBA8888)          /* 17 */ \
    NV(RGBA8888_Premultiplied,            = QImage::Format_RGBA8888_Premultiplied)          /* 18 */ \
    NV(BGR30,            = QImage::Format_BGR30)          /* 19 */ \
    NV(A2BGR30_Premultiplied,            = QImage::Format_A2BGR30_Premultiplied)          /* 20 */ \
    NV(size,)   \


class EIRPIXELIMAGE_EXPORT qiFormat : public Enumeration
{
    DECLARE_ENUMERATION(qiFormat, QIFORMAT_ENUM)
};

