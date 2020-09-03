#pragma once
#include "eirImage.h"

#include <QImage>
#include <QStringList>

#include <eirBase/Typedefs.h>

class QQImage : public QImage
{
public:
    QQImage();
    QQImage(const QImage &image);
    QQImage(const QString &fileName, const char *format = nullptr);

public: // static
    static QStringList supportedReadFormats();
    static QStringList supportedWriteFormats();
};



