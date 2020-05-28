//! \file cvCascade.cpp
#include "cvCascade.h"

#include <eirBase/Debug.h>

cvCascade::cvCascade()
{
    TRACEFN
    mpCascade = new cv::CascadeClassifier();
    EXPECTNE(nullptr, mpCascade);
}

bool cvCascade::load(cvString xmlCascadeFileName)
{
    TRACEQFI << xmlCascadeFileName.toString();
    EXPECTNE(nullptr, mpCascade);
    if ( ! mpCascade)    return false;
    return mpCascade->load(xmlCascadeFileName);
}
