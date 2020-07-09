#include "Region.h"

Region::Region() {;}
Region::Region(const QQRectF rcf) : mRectF(rcf) {;}
Region::Region(const QQRectF rcf, const QSize sz) { set(rcf, sz); }

QQRect Region::set(const QSize sz)
{
    return set(mRectF, sz);
}

QQRect Region::set(const QQRectF rcf, const QSize sz)
{
    mRectF = rcf, mSize = sz, mRegion.nullify();
    if (rcf.isValid())
    {
        if (rcf.isUnit())
        {
            mRegion.set(QQRectF(qreal(sz.width())  * rcf.x(),
                               qreal(sz.height()) * rcf.y(),
                               qreal(sz.width())  * rcf.width(),
                               qreal(sz.height()) * rcf.height()));
        }
        else if (rcf.isValid())
        {
            mRegion.set(rcf);
        }
    }
    return mRegion;
}

