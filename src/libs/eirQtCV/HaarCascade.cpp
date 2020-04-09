#include "HaarCascade.h"

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>

#include "cvString.h"

HaarCascade::HaarCascade(const QtOpenCV::ObjectType objType,
                         const VarMap &config)
    : mObjType(objType)
    , mConfig(config) {;}

ErrorHandler::Item HaarCascade::errorItem() const
{
    return mErrorItem;
}

bool HaarCascade::load(QFileInfo xmlFileInfo=QFileInfo())
{
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
    if ( ! xmlFileInfo.isFile())
        xmlFileInfo = QFileInfo(
                QDir(mConfig.value("DetectorDir")
                    .current().toString()),
                mConfig.value("FileName")
                    .current().toString());
    TRACEQFI << xmlFileInfo;
    if ( ! errorHandler()->tryFileMode(QIODevice::ReadOnly,
                                xmlFileInfo,
                                "HaarCascade XML file"))
        return false;
    cv::CascadeClassifier * cascade = new cv::CascadeClassifier();
    TSTALLOC(cascade);
    if ( ! errorHandler()->
         expect(cascade->load(cvString(xmlFileInfo.filePath())),
                "Loading HaarCascadeClassifier: "
                + xmlFileInfo.filePath()))
        return false;
    mpCascade = cascade;
    return true;
}

void HaarCascade::resetError()
{
    mErrorItem = ErrorHandler::Item();
}

void HaarCascade::setError(const ErrorHandler::Item &item)
{
    mErrorItem = item;
}
