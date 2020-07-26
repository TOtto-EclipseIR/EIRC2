#include "cvString.h"

cvString::cvString(const QString &qstring)
{
    assign(qstring.toStdString());
}
