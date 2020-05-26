//! \file HaarCatalog.cpp
#include "HaarCatalog.h"

#include <QFile>
#include <QDomElement>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>
#include <eirExe/XmlFile.h>

HaarCatalog::HaarCatalog(const HaarBase &haarBase)
    : HaarBase(haarBase)
{
    TRACEQFI << haarBase.baseDir();
}

int HaarCatalog::size() const
{
    return mNamesItemMap.size();
}

bool HaarCatalog::isValid() const
{
    TRACEFN
    if (mNamesItemMap.isEmpty())    return false;
    return true;
}

HaarCatalog::HaarCatalog(const QString &baseDirPath)
    : HaarBase(baseDirPath)
{
    TRACEQFI << baseDirPath;
}

bool HaarCatalog::load(const FileName &xmlFileName)
{
    TRACEQFI << xmlFileName;
    Success success(true);
    XmlFile xmlFile(baseFileName(xmlFileName));
    success.test(xmlFile.load());
    WEXPECTEQ("HaarDetectors", xmlFile.rootElement().tagName());
    for (QDomElement deClass = xmlFile.rootElement()
                                    .firstChildElement("DetectorClass");
         ! deClass.isNull();
         deClass = deClass.nextSiblingElement("DetectorClass"))
    {
        BasicName className = deClass.attribute("Name");
        BasicName defaultName = deClass.attribute("Default");
        TRACE << className();
        for (QDomElement deDetector = deClass.firstChildElement("Detector");
             ! deDetector.isNull();
             deDetector = deDetector.nextSiblingElement("Detector"))
        {
            BasicName cascadeName = deDetector.attribute("Name");
            TRACE << cascadeName();
            QString sizeWidth = deDetector.attribute("Width");
            QString sizeHeight = deDetector.attribute("Height");
            QSize detectorSize(sizeWidth.toInt(), sizeHeight.toInt());
            HaarCatalog::Item item(className, cascadeName, detectorSize,
                                   defaultName == cascadeName);
            item.parseDetectorElements(deDetector);
            HaarCatalog::Names names(className, cascadeName);
            mNamesItemMap.insert(names, item);
        } // for(deDetector)
    } // for (deClass)
    dump();
    return success;
}

HaarCatalog::Names::List HaarCatalog::namePairs() const
{
    TRACEFN
    HaarCatalog::Names::List pairs;
    foreach (HaarCatalog::Item item, mNamesItemMap.values())
    {
        Names pair(item.className(), item.cascadeName());
        pairs << pair;
    }
    return pairs;
}

FileName HaarCatalog::cascadeXmlFile(const BasicName &className,
                                     const BasicName &cascadeName)
{
    HaarCatalog::Names names(className, cascadeName);
    HaarCatalog::Item item = mNamesItemMap.value(names);
    return item.xmlFileName();
}

FileName HaarCatalog::defaultXmlFile(const BasicName &className)
{
    foreach (HaarCatalog::Item item, mNamesItemMap.values())
    {
        if (item.className() == className && item.isDefault())
            return item.xmlFileName();
    }
    return FileName();
}

void HaarCatalog::dump() const
{
    TRACEQFI << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< HaarCatalog";
    DUMP << "===HaarCatalog:";
    foreach (Item item, mNamesItemMap.values())
        item.dump();
}

HaarCatalog::Names::Names(const BasicName &className,
                          const BasicName &cascadeName)
{
    TRACEQFI << className() << cascadeName();
    set(className, cascadeName);
}

void HaarCatalog::Names::set(const BasicName &className,
                             const BasicName &cascadeName)
{
    TRACEQFI << className() << cascadeName();
    first = className, second = cascadeName;
}

BasicName HaarCatalog::Names::className() const
{
    return first;
}

BasicName HaarCatalog::Names::cascadeName() const
{
    return second;
}

QString HaarCatalog::Names::toString() const
{
    return  QString("%1/%2").arg(className()).arg(cascadeName());
}

HaarCatalog::Names::operator QString() const
{
    return toString();
}

QString HaarCatalog::Names::operator ()() const
{
    return toString();
}

HaarCatalog::Item::Item()
{
    TRACEFN
}

HaarCatalog::Item::Item(const BasicName &className,
                        const BasicName &cascadeName,
                        const QSize detectorSize,
                        const bool isDefault)
    : mClassName(className)
    , mCascadeName(cascadeName)
    , mDetectorSize(detectorSize)
    , mIsDefault(isDefault)
{
    TRACEQFI << className() << cascadeName() << detectorSize << isDefault;
}

HaarCatalog::Item::Item(const BasicName &className,
                        const BasicName &cascadeName,
                        const QSize detectorSize,
                        const FileName &xmlFileName,
                        const QString &description,
                        const bool isDefault)
    : mClassName(className)
    , mCascadeName(cascadeName)
    , mDetectorSize(detectorSize)
    , mXmlFileName(xmlFileName)
    , mDescription(description)
    , mIsDefault(isDefault)
{
    TRACEQFI << className() << cascadeName() << detectorSize
             << xmlFileName << isDefault << endl << description;
}

BasicName HaarCatalog::Item::className() const
{
    return mClassName;
}

BasicName HaarCatalog::Item::cascadeName() const
{
    return mCascadeName;
}

FileName HaarCatalog::Item::xmlFileName() const
{
    return mXmlFileName;
}

bool HaarCatalog::Item::isDefault() const
{
    return mIsDefault;
}

void HaarCatalog::Item::setDescription(const QString &description)
{
    mDescription = description;
}

void HaarCatalog::Item::setXmlFileName(const QString &xmlFileName)
{
    mXmlFileName = xmlFileName;
}

void HaarCatalog::Item::dump() const
{
    DUMP << QString("---Name: %1/%2 Size: %3x%4 XML: %5 %6")
            .arg(mClassName).arg(mCascadeName)
            .arg(mDetectorSize.width()).arg(mDetectorSize.height())
            .arg(mXmlFileName).arg(mIsDefault ? "Default" : "");
    DUMP << "  " << mDescription;
}

void HaarCatalog::Item::parseDetectorElements(const QDomElement &detector)
{
    TRACEQFI << detector.tagName();
    QString description;
    QString xmlFileName;
    QDomElement deDesc = detector.firstChildElement("Description");
    description = deDesc.text().simplified();
    QDomElement deFile = detector.firstChildElement("XmlFile");
    xmlFileName = deFile.text().simplified();
    WEXPECTNOT(description.isEmpty())
    WEXPECTNOT(xmlFileName.isEmpty())
    setDescription(description);
    setXmlFileName(xmlFileName);
}
