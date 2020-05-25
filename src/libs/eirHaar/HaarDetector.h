//! \file HaarCascade.h
#pragma once
#include "eirHaar.h"

#include <QList>
#include <QRect>

#include <eirExe/Configuration.h>

#include "HaarCascade.h"

class HaarDetector
{
public:
    HaarDetector();
    bool set(HaarCascade *cascade);
    void set(const Configuration &config);
    bool set(const QImage &image);
    int detect() const; // const?
    QList<QRect> rectangleList();
};

