//! \file XmlFile.h
#pragma once
#include "eirExe.h"

#include <QDomDocument>
#include <QDomElement>

#include "FileName.h"

class EIREXE_EXPORT XmlFile
{
public:
    XmlFile();
    XmlFile(const FileName &fileName);
    bool load(const FileName &fileName);
    bool load();
    QDomDocument document() const;
    QDomElement rootElement() const;

private:
    FileName mFileName;
    QDomDocument mDomDocument;
    QDomElement mRootElement;
};

