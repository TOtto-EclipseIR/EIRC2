//! \file HaarCatalog.h
#pragma once
#include "eirHaar.h"

#include <QMap>
#include <QPair>
#include <QSize>

#include <eirBase/BasicName.h>
#include <eirExe/Configuration.h>
#include <eirExe/FileName.h>

class EIRHAAR_EXPORT HaarCatalog
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
    }; // HaarCatalog::Names

public:
    class Item
    {
    public:
        Item();
        Item(const BasicName &className,
             const BasicName &cascadeName,
             const QSize detectorSize,
             const FileName xmlFileName);

    private:
        BasicName mClassName;
        BasicName mCascadeName;
        QSize mDetectorSize;
        FileName mXmlFileName;

    }; // HaarCatalog::Item

public:
    HaarCatalog();
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

private:
    QMap<Names, Item> mNamesItemMap;

};

