#include "BaseImage.h"

#include <eirBase/Debug.h>

BaseImage::BaseImage(const QImage::Format format)
    //: QImage(format)
{
    TRACEQFI << format;
    WANTDO(DeleteMe)
}
