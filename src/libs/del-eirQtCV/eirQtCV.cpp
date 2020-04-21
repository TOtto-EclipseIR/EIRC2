#include "eirQtCV.h"

#include <eirBase/ErrorHandler.h>

eirQtCV::eirQtCV()
{
    registerErrors();
}

void eirQtCV::registerErrors()
{
    ErrorHandler::Item::registerCode(
         "eirQtCV/Detector/CtorCascade",
         QtFatalMsg,
         "Unable to constuct %What",
         VarMap() << Var("What",
                "QtCVobjdetect cv::CascadeClassifier"));
    ErrorHandler::Item::registerCode(
         "eirQtCV/Detector/CascadeLoad",
         QtFatalMsg,
         "Unable to constuct %What",
         VarMap()
            << Var("What", "QtCVobjdetect cv::CascadeClassifier")
            << Var("FilePath", "Specified Cascade XML File"));

}

QStringList eirQtCV::imageReadNameFilters()
{
    QStringList filters;
    filters << "*.BMP" << "*.JPG" << "*.PNG";
    return filters;
}
