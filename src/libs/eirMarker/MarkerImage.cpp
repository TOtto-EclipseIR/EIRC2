#include "MarkerImage.h"

#include <eirXfr/Debug.h>


MarkerImage::MarkerImage(const FramePak &pak,
                         QObject *parent)
    : cmFramePak(pak)
{
    TRACEQFI << cmFramePak() << QOBJNAME(parent);
}
