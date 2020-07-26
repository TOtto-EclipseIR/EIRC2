#pragma once
#include "eirQtCV.h"

#include <QString>

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>

class EIRQTCV_EXPORT cvString : public std::string
{
public:
    cvString(const QString &qstring);
};

