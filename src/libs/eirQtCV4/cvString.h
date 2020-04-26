#pragma once

#include <opencv2/core/cvstd.hpp>

#include <QByteArray>
#include <QString>

#include <eirBase/MultiName.h>

class cvString : public cv::String
{
public:
    cvString();
    cvString(const cv::String cvs);
    cvString(const QByteArray &qba);
    cvString(const QString &qs);
    cvString(const MultiName &qs);
    void set(const QByteArray &qba);
    QByteArray toByteArray() const;
    operator QByteArray() const;
};

