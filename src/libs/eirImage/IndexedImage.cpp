// file:{EIRC2 repo}./src/libs/eirImage/IndexedImage.cpp
#include "IndexedImage.h"

#include <eirBase/Debug.h>

IndexedImage::IndexedImage(const ColorTable &colorTable,
                           const QSize size,
                           const QImage::Format format)
    : BaseImage(size, format)
    , mColorTable(colorTable)
{
    TRACEQFI << colorTable.colorCount() << size << format;
}

IndexedImage::IndexedImage(const QImage &image,
                           const ColorTable &newColorTable,
                           const QImage::Format newFormat)
    : BaseImage(image, newFormat)
    , mColorTable(newColorTable)
{
    TRACEQFI << image << mColorTable.colorCount()
             << newFormat;
    MUSTDO(Transform)
}

