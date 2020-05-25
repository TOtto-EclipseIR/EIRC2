#pragma once

#include <QString>

class FileName
{
public:
    FileName(const QString *qstr);
    void set(const QString *qstr);
    QString toString() const;
    operator QString () const;

private:
    QString mQString;
};

