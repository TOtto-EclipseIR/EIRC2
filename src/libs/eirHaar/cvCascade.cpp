//! \file cvCascade.cpp
#include "cvCascade.h"

#include <eirBase/Debug.h>

cvCascade::cvCascade()
//    : cv::CascadeClassifier()
{
    TRACEFN
    mpCascade = new cv::CascadeClassifier();
    EXPECTNE(nullptr, mpCascade);
    if ( ! mpCascade)    return;
}

cvCascade::cvCascade(cvString xmlCascadeFileName)
//    : cv::CascadeClassifier(xmlCascadeFileName)
{
    TRACEQFI << xmlCascadeFileName.toString();
    mpCascade = new cv::CascadeClassifier(xmlCascadeFileName);
    EXPECTNE(nullptr, mpCascade);
    if ( ! mpCascade)    return;
}

bool cvCascade::load(cvString xmlCascadeFileName)
{
    TRACEQFI << xmlCascadeFileName.toString();
    EXPECTNE(nullptr, mpCascade);
    if ( ! mpCascade)    return false;
    return mpCascade->load(xmlCascadeFileName);
}
