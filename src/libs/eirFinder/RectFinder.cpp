#include "RectFinder.h"

#include <QPainter>

#include <eirXfr/Debug.h>

RectFinder::RectFinder(ConfigObject *cfgObj,
                       QObject *parent)
{
    TRACEQFI << QOBJNAME(cfgObj) << QOBJNAME(parent);
    mpConfigObject = cfgObj;
    for (CascadeType ct = CascadeType::nullCascadeType;
         ct < CascadeType::sizeCascadeType;
         ++ct)
    {
        mCascades.set(ct, cvCascade(ct, mpConfigObject));
    }
}

void RectFinder::set(ConfigObject *cfgObj)
{
    mpConfigObject = cfgObj;
}

void RectFinder::set(const QDir &baseCascadeDir)
{
    TRACEQFI << baseCascadeDir << baseCascadeDir.exists() << baseCascadeDir.isReadable();
    mBaseCascadeDir = baseCascadeDir;
}

bool RectFinder::loaded(const CascadeType &cascadeType) const
{
    return mCascades.at(cascadeType).isLoaded();
}

cvCascade RectFinder::cascade(const CascadeType &cascadeType) const
{
    return mCascades.at(cascadeType);
}

QImage RectFinder::findRectImage(const CascadeType &cascadeType) const
{
    TRACEQFI << cascadeType();
    return cascade(cascadeType).findRectImage();
}

QQRectList RectFinder::rectangleList(const CascadeType &cascadeType)
{
    return mRectLists.at(cascadeType);
}

QImage RectFinder::makeRectImage(const CascadeType &cascadeType, bool all)
{
    TRACEQFI << cascadeType.name() << all;
    NEEDUSE(all);
    QImage rectImage = findRectImage(cascadeType);
    QPainter painter;
    painter.begin(&rectImage);
    painter.setPen(Qt::blue);
    QBrush brush(Qt::blue);
    QPen pen(brush, all ? 1 : 3);
    painter.setPen(pen);
    foreach (QRect rc, rectangleList(cascadeType))
        painter.drawRect(rc);
    painter.end();
    return rectImage;
}

void RectFinder::load(const CascadeType &cascadeType,
                      const QFileInfo &xmlFileInfo)
{
    TRACEQFI << cascadeType.name() << xmlFileInfo;
    cvCascade & cvc = mCascades.at(cascadeType);
    cvc.clear();
    TRACE << xmlFileInfo << xmlFileInfo.exists()
          << xmlFileInfo.isReadable() << xmlFileInfo.isFile();
    WEXPECT(xmlFileInfo.exists());
    WEXPECT(xmlFileInfo.isReadable());
    WEXPECT(xmlFileInfo.isFile());
    WEXPECT(xmlFileInfo.isFile());
    cvCascade newCvc(cascadeType, mpConfigObject);
    if (newCvc.load(xmlFileInfo.filePath()))
        cvc = newCvc;
}

void RectFinder::configure(const Configuration &baseConfig)
{
    TRACEFN;
    baseConfig.dump();
    mConfigurations.set(CascadeType::nullCascadeType, baseConfig);
}

void RectFinder::configure(const CascadeType cascadeType,
                           const Configuration &cascadeConfig)
{
    TRACEQFI << cascadeType.name();
    cascadeConfig.dump();
    mConfigurations.set(cascadeType, cascadeConfig);
}

void RectFinder::set(const CascadeType &cascadeType,
                     const QImage &image)
{
    TRACEQFI << cascadeType() << image.size() << image.format();
    mCascades.at(cascadeType).setImage(image);
}

void RectFinder::findRectangles(const CascadeType &cascadeType)
{
    TRACEQFI << cascadeType();
    mCascades.at(cascadeType).findRectangles();
}
