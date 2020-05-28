//! \file HaarBase.h
#pragma once
#include "eirHaar.h"

#include <QString>

#include <string> // std:: Standard C++ Library

class EIRHAAR_EXPORT cvString : public std::string
{
public:
    cvString();
    cvString(const QString &qString);
    QString toString() const;
};

