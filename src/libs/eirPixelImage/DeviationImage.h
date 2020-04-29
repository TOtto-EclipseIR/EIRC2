#pragma once

#include "BaseDeviation.h"
#include "ColorImage.h"


class DeviationImage : public ColorImage
{
public:
    DeviationImage();

    void create();

protected:
    ColorImage mSampleImage;
    ColorImage mDeviationImage;
};

