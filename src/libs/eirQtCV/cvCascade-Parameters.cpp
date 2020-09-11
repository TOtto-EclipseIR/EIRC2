//! @file {EIRC2 repo}/src/libs/eirQtCV/cvCascade-Parameters.cpp

#include "cvCascade.h"

#include <eirXfr/Debug.h>

cvCascade::Parameters::Parameters() {;}

cvCascade::Parameters::Parameters(const Configuration &cascadeConfig)
{
    set(cascadeConfig);
}

void cvCascade::Parameters::set(const Configuration &cascadeConfig)
{
    TRACEFN;
    cascadeConfig.dump();
    mConfig = cascadeConfig;
}

void cvCascade::Parameters::calculate(const cvCascade::Type type,
                                      const QQSize imageSize,
                                      const QQSize coreSize)
{
    TRACEQFI << cvCascade::typeName(type)() << imageSize << coreSize;
    NEEDUSE(type);

    qreal typeFactor = qQNaN(); // object portion of shoulder-to-shoulder
    switch (type)
    {
    case PreScan:
    case PreScanAll:
    case Face:          typeFactor = 1.0 / 3.0;     break;
    default:            MUSTDO(others);             break;
    }
    BEXPECTNOT(qIsNaN(typeFactor));

    int minWidth = coreSize.width();
    int maxWidth = imageSize.minDimension();
    int minAcross = mConfig.unsignedInt("MinAcross");
    int maxAcross = mConfig.unsignedInt("MaxAcross");
    if (minAcross)
        minWidth = qreal(imageSize.width()) / qreal(minAcross)
                        / qreal(coreSize.width()) * typeFactor;
    if (maxAcross)
        maxWidth *= qreal(maxWidth) / qreal(maxAcross)
                        / qreal(coreSize.width()) * typeFactor;
    mMinSize.setWidth(minWidth, coreSize.aspect());
    /*
    QSize sz = DetectorSize;
    qreal s1 = qMin((qreal)scaled_size.height() / (qreal)sz.height() / ClassFactor,
                    (qreal)scaled_size.width()  / (qreal)sz.width()  / ClassFactor);
    qreal s2 = s1;

    if (MinAcross)
        s1 = qMax(1.0, (qreal)scaled_size.width() / (qreal)MinAcross
                / (qreal)sz.width() * ClassFactor);
    if (MaxPixels)
        s2 = qMax(1.0, (qreal)MaxPixels / (qreal)sz.width());
    sz *= qMin(s1, s2);
    return sz.boundedTo(scaled_size);    */

    double fac = parseFactor();
    mFactor = qIsNull(fac) ? 1.160 : fac;
    NEEDDO("Default Based on Image/Core size & MaxDetectors, etc.");

    int neigh = mConfig.signedInt("Neighbors");
    mNeighbors = (neigh >= 0) ? neigh : 2;

    DUMP << dumpList();
}

double cvCascade::Parameters::factor() const
{
    return mFactor;
}

int cvCascade::Parameters::neighbors() const
{
    return mNeighbors;
}

int cvCascade::Parameters::flags() const
{
    return mFlags;
}

QQSize cvCascade::Parameters::minSize() const
{
    return mMinSize.isValid() ? mMinSize : QQSize::null;
}

QQSize cvCascade::Parameters::maxSize() const
{
    return mMaxSize.isValid() ? mMaxSize : QQSize::null;
}

QString cvCascade::Parameters::methodString(const QFileInfo &cascadeXmlInfo) const
{
    return QString("Factor=%1,Neighbors=%2,MinSize=%3x%4,MaxSize=%5x%6,%7")
            .arg(factor()).arg(neighbors())
            .arg(minSize().width()).arg(minSize().height())
            .arg(maxSize().width()).arg(maxSize().height())
            .arg(cascadeXmlInfo.completeBaseName());
}

QVariant cvCascade::Parameters::toVariant() const
{
    return QVariant::fromValue(*this);
}

cvCascade::Parameters::operator QVariant() const
{
    return toVariant();
}

double cvCascade::Parameters::parseFactor()
{
    double result=qQNaN();
    double f = mConfig.real("Factor");
    if (f >= 1.001 && f <= 2.000)
        result = 0.0;
    else if (f > 1.0 && f < 999.0)
        result = 1.000 + f / 1000.0;
    else
        result = 0.0; // let algo decide
    TRACE << f << result;
    BEXPECTNOT(qIsNaN(result));
    return result;
}

QStringList cvCascade::Parameters::dumpList() const
{
    QStringList qsl;
    qsl << QString("%1 = %2").arg("factor").arg(factor());
    qsl << QString("%1 = %2").arg("neighbors").arg(neighbors());
    qsl << QString("%1 = %2").arg("flags").arg(flags());
    qsl << QString("%1 = %2x%3").arg("minSize").arg(minSize().width())
                                               .arg(minSize().height());
    qsl << QString("%1 = %2x%3").arg("maxSize").arg(maxSize().width())
                                               .arg(maxSize().height());
    return qsl;
}

