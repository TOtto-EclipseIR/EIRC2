#include "HaarCascade.h"

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>

#include "cvString.h"

HaarCascade::HaarCascade(const QtOpenCV::ObjectType objType,
                         const VarMap &config)
    : mUid(Uid::create())
    , mObjType(objType)
    , mConfig(config) {;}

ErrorHandler::Item HaarCascade::errorItem() const
{
    return mErrorItem;
}

bool HaarCascade::load(QFileInfo xmlFileInfo=QFileInfo())
{
    TRACEQFI << xmlFileInfo << mObjType;
    if (mpCascade)
    {
        delete mpCascade;
        mpCascade = nullptr;
    }
#if 1
    NEEDDO(It Right!)
    xmlFileInfo = QFileInfo(QDir("../Detectors"),
                            "DefaultFrontalFace.xml");
#else
    if ( ! xmlFileInfo.isFile())
        xmlFileInfo = QFileInfo(
                QDir(mConfig.value("DetectorDir")
                    .current().toString()),
                mConfig.value("FileName")
                    .current().toString());
#endif
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

void HaarCascade::destroy()
{
    TRACEQFI << mObjType;
    if (mpCascade) delete mpCascade;
}

Uid HaarCascade::uid() const
{
    return mUid;
}

void HaarCascade::resetError()
{
    mErrorItem = ErrorHandler::Item();
}

void HaarCascade::setError(const ErrorHandler::Item &item)
{
    mErrorItem = item;
}
