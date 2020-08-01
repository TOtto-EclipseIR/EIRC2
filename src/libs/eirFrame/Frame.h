#pragma once

#include <QImage>

#include <QDomDocument>
#include <QDomElement>
#include <QFileInfo>

class Frame : public QImage
{
public:
    Frame();
    Frame(const QImage &other);
    QFileInfo fileInfo() const;
    void setFileInfo(const QFileInfo fileInfo);

protected:
    QDomDocument domDocument() const;
    QDomElement domElement() const;
    void set(const QDomDocument &doc);
    void set(const QDomElement &de);
};

