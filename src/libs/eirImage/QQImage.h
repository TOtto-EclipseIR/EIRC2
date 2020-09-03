#pragma once
#include "eirImage.h"

#include <QImage>

class QQImage : public QImage
{
public:
    QQImage();
    QQImage(const QImage &image);
    QQImage(const QString &fileName, const char *format = nullptr);
};



