// file: {EIRC2 repo}./src/libs/eirPixelImage/GreyAverageImage.cpp
#include "GreyAverageImage.h"

#include <eirBase/Debug.h>

GreyAverageImage::GreyAverageImage()
    : mSubjectImage(ColorImage())
    , mGreyAverageImage(ColorImage())
{
    TRACEFN
}

ColorImage GreyAverageImage::create(ColorImage greyColorImage)
{
    TRACEQFI << greyColorImage;
    ColorImage trueGreyColorImage(greyColorImage.size(),
                                  Format_ARGB32);
#if 1
    NEEDDO(What?)
#else
    ColorImage trueGreyColorImage(greyColorImage.size(),
                                  Format_ARGB32);

    if ( greyColorImage.notColor32Format())
        greyColorImage.convertTo(Format_ARGB32);

    for (int row = 0; row < greyColorImage.height(); ++row)
    {
        QRgb * pRgbInp = (QRgb *)(greyColorImage.scanLine(row));
        QRgb * pRgbOup = (QRgb *)(trueGreyColorImage.scanLine(row));
        int k = greyColorImage.bytesPerLine();
        while (k)
        {
            QRgb qrgb = *pRgbInp++;
            int grey = qGray(qrgb);
            QRgb out = qRgb(grey, grey, grey);
            *pRgbOup++ = out;
            k -= sizeof(QRgb);
        }
    }
#endif
    return trueGreyColorImage;
}

ColorImage GreyAverageImage::subjectImage() const
{
    return mSubjectImage;
}

ColorImage GreyAverageImage::greyAverageImage() const
{
    return mGreyAverageImage;
}

bool GreyAverageImage::isGrey()
{
    return BaseImage::isGrey();
}

QImage GreyAverageImage::image() const
{
    return greyAverageImage();
}
