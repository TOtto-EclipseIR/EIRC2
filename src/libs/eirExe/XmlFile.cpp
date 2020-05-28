#include "XmlFile.h"

#include <QFile>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>

XmlFile::XmlFile()
{
    TRACEFN
}

XmlFile::XmlFile(const FileName &fileName)
    : mFileName(fileName)
{
    TRACEQFI << fileName;
}

bool XmlFile::load(const FileName &fileName)
{
    mFileName = fileName;
    return load();
}

bool XmlFile::load()
{
    TRACEQFI << mFileName;
    Success success(true);
    success.testNot(mFileName().isEmpty());
    QFile file(mFileName);
    EXPECT(file.open(QIODevice::ReadOnly));
    QByteArray qba= file.readAll();
    file.close();
    EXPECTNOT(qba.isEmpty());
    success.testNot(qba.isEmpty());
    success.test(mDomDocument.setContent(qba));
    success.testNot(mDomDocument.isNull());
    mRootElement = mDomDocument.documentElement();
    success.testNot(mRootElement.isNull());
    return success;
}

QDomDocument XmlFile::document() const
{
    return mDomDocument;
}

QDomElement XmlFile::rootElement() const
{
    return mRootElement;
}
