#pragma once

#include <QObject>

class ImagePakWriterQueue : public QObject
{
    Q_OBJECT
public:
    explicit ImagePakWriterQueue(QObject *parent = nullptr);

signals:

};

