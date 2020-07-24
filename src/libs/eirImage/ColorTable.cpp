#include "ColorTable.h"

#include <eirXfr/Debug.h>

ColorTable::ColorTable(bool fillBlack)
{
    TRACEQFI << fillBlack;
    if (fillBlack) fill(0, 256);
}

ColorTable::ColorTable(const QVector<QRgb> &other)
    : mColorVector(other)
{
    TRACEQFI << mColorVector.size();
}

bool ColorTable::isEmpty() const
{
    return mColorVector.isEmpty();
}

void ColorTable::fill(const QRgb color, int count)
{
    if (count < 1)
    {
        if (mColorVector.isEmpty())
            count = 0;
        else
            count = colorCount();
    }
    mColorVector.fill(color, count);
}

int ColorTable::colorCount() const
{
    return mColorVector.size();
}
