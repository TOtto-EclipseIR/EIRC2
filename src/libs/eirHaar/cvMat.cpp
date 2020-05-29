
#include "cvMat.h"

#include <eirBase/Debug.h>

cvMat::cvMat() { TRACEFN }
cvMat::cvMat(const Image &image, const cvFormat &newFormat)
{
    TRACEQFI << image.size()  << newFormat();
}
