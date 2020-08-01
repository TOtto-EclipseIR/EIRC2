#include "Frame.h"

#include <QDir>

Frame::Frame() {;}
Frame::Frame(const QImage &other) : QImage(other) {;}

QFileInfo Frame::fileInfo() const
{
    return QFileInfo(QDir(text("FileInfoDir")),
                     text("FileInfoName"));
}

void Frame::setFileInfo(const QFileInfo fileInfo)
{
    setText("FileInfoDir", fileInfo.dir().path());
    setText("FileInfoName", fileInfo.fileName());
}

QDomDocument Frame::domDocument() const
{
    QString docString = text("DomDocument");
    QDomDocument doc;
    doc.setContent(docString);
    return doc;
}

QDomElement Frame::domElement() const
{
    return domDocument().documentElement();
}

void Frame::set(const QDomDocument &doc)
{
    setText("DomDocument", doc.toString(4));
}

void Frame::set(const QDomElement &de)
{
    QDomDocument doc("ImageDomDocument");
    QDomElement root = doc.createElement("documentElement");
    root.appendChild(de);
    doc.appendChild(root);
    set(doc);
}

