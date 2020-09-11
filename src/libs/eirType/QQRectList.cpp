// file: {EIRC2 repo)./src/libs/eirType/QQRectList.cpp
#include "QQRectList.h"

QQRectList::QQRectList(const QList<QQRect> rects)
{
    set(rects);
}

void QQRectList::set(const QList<QQRect> &rects)
{
    QList<QQRect>::clear();
    QList<QQRect>::append(rects);
}

void QQRectList::set(const QVariant &variant)
{
    set(variant.value<QQRectList>());
}

QRectVector QQRectList::vector() const
{
    QRectVector vec;
    foreach (QQRect rc, mid(0)) vec << QRect(rc);
    return vec;
}

QVariant QQRectList::toVariant() const
{
    return QVariant::fromValue(*this);
}

QQRectList::operator QVariant() const
{
    return toVariant();
}


QList<QRect> QQRectList::list() const
{
    QList<QRect> list;
    foreach (QQRect qqrc, mid(0)) list << QRect(qqrc);
    return list;
}
