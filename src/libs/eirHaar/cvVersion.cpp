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
    insert("OpenCV/Version/Copyright", "Copyright (C) 2019-2020, Xperience AI, all rights reserved.");
}

QString cvVersion::toString() const
{
    int major = value("OpenCV/Version/Major").value().toInt();
    int minor = value("OpenCV/Version/Minor").value().toInt();
    int release = value("OpenCV/Version/Release").value().toInt();
    QString status = value("OpenCV/Version/Status").value().toString();
    QString copyright = value("OpenCV/Version/Copyright").value().toString();
    return QString("OpenCV v%1.%2.%3%4 %5").arg(major).arg(minor)
            .arg(release).arg(status).arg(copyright);
}

QString cvVersion::operator ()() const
{
    return toString();
}

cvVersion::operator QString() const
{
    return toString();
}
