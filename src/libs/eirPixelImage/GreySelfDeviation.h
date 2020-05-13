#pragma once

#include "BaseDeviation.h"
#include "DeviationImage.h"
#include "ColorImage.h"
#include "GreyAverageImage.h"


class GreySelfDeviation : public ColorImage, public BaseDeviation
{
public:
    GreySelfDeviation();

    void create();

protected:
    GreyAverageImage mGreyAverageImage;
    DeviationImage mDeviationImage;
};

