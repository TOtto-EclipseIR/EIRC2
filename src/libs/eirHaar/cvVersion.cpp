#include "cvVersion.h"

//#include "../../../3rd/OpenCV4/install/include/opencv2/opencv.hpp"
//#include "../../../3rd/OpenCV4/install/include/opencv2/core/core.hpp"
#include "../../../3rd/OpenCV4/install/include/opencv2/core/version.hpp"
//#include "../../../3rd/OpenCV4/install/include/opencv2/objdetect/objdetect.hpp"

cvVersion::cvVersion()
{
    setName("OpenCV/Version");
    insert("OpenCV/Version/Major", CV_VERSION_MAJOR);
    insert("OpenCV/Version/Minor", CV_VERSION_MINOR);
    insert("OpenCV/Version/Revision", CV_VERSION_REVISION);
    insert("OpenCV/Version/Status", CV_VERSION_STATUS);
}
