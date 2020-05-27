#include "cvString.h"

#include <string>

cvString::cvString() {;}

cvString::cvString(const QString &qString)
    : std::string((char *)(qString.toLocal8Bit().data()))
{
}

QString cvString::toString() const
{
    return QString::fromStdString(*this);
}
