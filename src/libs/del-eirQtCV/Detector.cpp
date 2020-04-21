// file: {EIRC2 repo}./src/lib/eirQtCV/Detector.h
#include "Detector.h"

#include <eirBase/Debug.h>

#include "cvString.h"


Detector::Detector(const ObjectType objType, QObject *parent)
    : QObject(parent)
    , cmUid(Uid::create())
    , cmObjectType(objType)
{
    TRACEQFI << objType.name();
    setObjectName("Detector:" + objType.name());
    WANTDO(Implement asynch slot/signals);
}

Uid Detector::uid() const
{
    return cmUid;
}

ObjectType Detector::objectType() const
{
    return cmObjectType;
}

bool Detector::initialize(const QFileInfo &qfiXml,
                          const VarPak &config)
{
    TRACEQFI << qfiXml << config.id().name()();
    mConfiguration = config;

    mpCascade = new cv::CascadeClassifier();
    WANTDO(Refactor ErrorHandler::tryFileMode())
    if (nullptr == mpCascade)
    {

        ErrorHandler::Item ei("eirQtCV/Detector/CtorCascade");
        setError(ei);
        return false;
    }
    if ( ! mpCascade->load(cvString(qfiXml.filePath())))
    {
        VarMap vars;
        vars.insert(Var("FilePath", qfiXml.absoluteFilePath()));
        ErrorHandler::Item ei("eirQtCV/Detector/CascadeLoad", vars);
        setError(ei);
        return false;
    }

    TODO(More?)
    return true;
}
