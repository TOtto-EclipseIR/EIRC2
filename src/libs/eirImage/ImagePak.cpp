#include "ImagePak.h"

#include <eirBase/Debug.h>

#include "ImageInfo.h"

ImagePak::ImagePak() {;}

ImagePak::ImagePak(const QFileInfo &fileInfo, const Image &baseImage)
{
    TRACEQFI << fileInfo << ImageInfo(baseImage)();
}
