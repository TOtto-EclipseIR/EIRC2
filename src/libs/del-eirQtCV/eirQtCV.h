#pragma once
#include "eirQtCV_global.h"

#include <QStringList>

#if 0
//#include <opencv2/opencv.hpp>
#include "D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include\opencv2\opencv_modules.hpp"
#include "D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include\opencv2\opencv.hpp"
//#include <opencv2/core.hpp>
#include "D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include\opencv2\core.hpp"
//#include <opencv2/core/mat.hpp>
#include "D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include\opencv2\core\mat.hpp"
//#include <opencv2/objdetect.hpp>
#include "D:\git\github.com\EIRC2\src\3rd\OpenCV4\install\include\opencv2\objdetect.hpp"
#endif

class EIRQTCV_EXPORT eirQtCV
{
public:
    eirQtCV();
    void registerErrors();
    static QStringList imageReadNameFilters();
};
