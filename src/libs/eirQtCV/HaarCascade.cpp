#include "HaarCascade.h"

#include <eirBase/Debug.h>
#include <eirExe/ErrorHandler.h>

HaarCascade::HaarCascade()
{

}

bool HaarCascade::load(const QFileInfo &xmlFileInfo)
{
    TRACEQFI << xmlFileInfo;
    errorHandler()->tryFileMode(QIODevice::ReadOnly,
                                xmlFileInfo,
                                "HaarCascade XML file");
//    WEXPECT(xmlFileInfo.exists())
    mpCascade = new cv::CascadeClassifier();
    return mpCascade->load(xmlFileInfo.absoluteFilePath().toStdString());
}
