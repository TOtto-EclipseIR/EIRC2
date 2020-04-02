#include "HaarCascade.h"

#include <eirBase/Debug.h>

HaarCascade::HaarCascade()
{

}

bool HaarCascade::load(const QFileInfo &xmlFileInfo)
{
    TRACEQFI << xmlFileInfo;
    WEXPECT(xmlFileInfo.exists())
            mpCascade = new cv::CascadeClassifier();
    return mpCascade->load(xmlFileInfo.absoluteFilePath().toStdString());
}
