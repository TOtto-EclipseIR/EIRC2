//! \file HaarCatalog.h
#pragma once
#include "eirHaar.h"

#include "HaarBase.h"

#include <QDomElement>
#include <QMap>
#include <QPair>
#include <QSize>

#include <eirBase/BasicName.h>
#include <eirExe/Configuration.h>
#include <eirExe/FileName.h>

class EIRHAAR_EXPORT HaarCatalog : public HaarBase
{
public:
    class Names : QPair<BasicName, BasicName>
    {
    public:
        Names(const BasicName &className, const BasicName &cascadeName);
        void set(const BasicName &className,
                 const BasicName &cascadeName);
        BasicName className() const;
        BasicName cascadeName() const;
        QString toString() const;
        operator QString () const;
        QString operator () () const;
    }; // HaarCatalog::Names

public:
    class Item
    {
    public:
        Item();
        Item(const BasicName &className,
             const BasicName &cascadeName,
             const QSize detectorSize,
             const bool isDefault=false);
        Item(const BasicName &className,
             const BasicName &cascadeName,
             const QSize detectorSize,
             const FileName &xmlFileName,
             const QString &description,
             const bool isDefault=false);
        void parseDetectorElements(const QDomElement &detector);
        void setDescription(const QString &description);
        void setXmlFileName(const QString &xmlFileName);
        void dump() const;

    private:

    private:
        BasicName mClassName;
        BasicName mCascadeName;
        QSize mDetectorSize;
        FileName mXmlFileName;
        QString mDescription;
        bool mIsDefault=false;
    }; // HaarCatalog::Item

public:
    HaarCatalog(const QString &baseDirPath=QString());
    HaarCatalog(const HaarBase &haarBase);
    bool load(const FileName &xmlFileName);
    void configure(const Configuration &config); // Detect/Resources/Catalog
    BasicName::List classNames() const;
    BasicName::List cascadeNames(const BasicName &className) const;
    BasicName defaultName(const BasicName &className);
    Item item(const BasicName &className,
                            const BasicName &cascadeName);
    FileName cascadeXmlFile(const BasicName &className,
                            const BasicName &cascadeName);
    FileName defaultXmlFile(const BasicName &className);
    void dump() const;

private:
    QMap<QString, Item> mNamesItemMap;

};

