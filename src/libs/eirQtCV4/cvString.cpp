#include "cvString.h"

cvString::cvString() : cv::String("") {;}
cvString::cvString(const cv::String cvs) : cv::String(cvs) {;}

cvString::cvString(const QString &qs)
{
    set(qs.toUtf8());
}

cvString::cvString(const MultiName &qs)
{
    set(qs.toString().toLocal8Bit());
}

void cvString::set(const QByteArray &qba)
{
    *this = qba.toStdString();
}

QByteArray cvString::toByteArray() const
{
    return QByteArray::fromStdString(*this);
}

cvString::operator QByteArray() const
{
    return toByteArray();
}
