#pragma once
#include "eirImage.h"

#include <QImage>
#include <QStringList>

#include <eirBase/Typedefs.h>

class EIRIMAGE_EXPORT QQImage : public QImage
{
public:
    QQImage();
    QQImage(const QImage &other);
    QQImage(const QString &fileName, const char *format = nullptr);
    int rows() const;
    int cols() const;

public: // static
    static QStringList supportedReadFormats();
    static QStringList supportedWriteFormats();
    static QStringList dirNameFilters(const QStringList suffixList);
    static QString dialogNameFilter(const QStringList suffixList);


};



