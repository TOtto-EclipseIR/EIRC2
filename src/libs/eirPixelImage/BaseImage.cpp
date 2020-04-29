// file: {EIRC2 repo}./src/libs/eirPixelImage/BaseImage.cpp
#include "BaseImage.h"

BaseImage::BaseImage()
{

}

BaseImage::BaseImage(const QImage &image)
    : QImage(image)
{

}

BaseImage::BaseImage(const QSize size, const QImage::Format format)
    : QImage(size, format)
{

}

bool BaseImage::isGrey() const
{
    if (QImage::Format_Grayscale8 == cmBaseImage.format())
        return true;
    QImage inImage = cmBaseImage;
    if (notColor32Format())
        inImage.convertTo(QImage::Format_ARGB32);
    for (int row = 0; row < inImage.height(); ++row)
    {
        uchar * pRow = inImage.scanLine(row);
        QRgb * pRgb = (QRgb *)(pRow);
        int k = inImage.bytesPerLine();
        while (k)
        {
            QRgb rgb = *pRgb++;
            if (qRed(rgb) != qGreen(rgb) || qRed(rgb) != qBlue(rgb))
                return false;
            k -= sizeof(QRgb);
        }
    }
    return true;
}

bool BaseImage::isNull() const
{
    return QImage::size().isNull() || QImage::isNull();
}

bool BaseImage::isColor32Format() const
{
    return isColor32Format(cmBaseImage);
}

bool BaseImage::notColor32Format() const
{
    return ! isColor32Format();
}

// static
bool BaseImage::isColor32Format(const QImage::Format imageformat)
{
    return (Format_ARGB32 == imageformat
            || Format_RGB32 == imageformat
            || Format_BGR888 == imageformat
            || Format_ARGB32_Premultiplied == imageformat
            || Format_RGBA8888_Premultiplied == imageformat);
}

// static
bool BaseImage::isColor32Format(const QImage &image)
{
    return isColor32Format(image.format());
}
