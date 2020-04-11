#include "eirQtCV.h"

eirQtCV::eirQtCV()
{
}

QStringList eirQtCV::imageReadNameFilters()
{
    QStringList filters;
    filters << "*.BMP" << "*.JPG" << "*.PNG";
    return filters;
}
