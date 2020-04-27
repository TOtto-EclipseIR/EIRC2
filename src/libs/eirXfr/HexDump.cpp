#include "HexDump.h"


HexDump::HexDump()
{

}

HexDump::HexDump(const void *data, const int bytes,
                 const MultiName &name)
    : cmpData((qptrdiff *)(data))
    , cmBytes(bytes)
    , cmName(name)
{

}

HexDump::HexDump(const QByteArray &ba, const MultiName &name)
    : cmpData((qptrdiff *)(ba.data()))
    , cmBytes(ba.size())
    , cmName(name)
{

}

void HexDump::format()
{
    QStringList qsl;
    qsl << QString("@0x%2 L%3 0x%4 %1").arg(cmName())
           .arg((ptrdiff_t)(cmpData), 2 * sizeof(ptrdiff_t), 16, QChar('0'))
           .arg(cmBytes).arg(cmBytes, 0, 16, QChar('0'));

    mStrings = qsl;
}
