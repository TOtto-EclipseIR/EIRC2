#pragma once

#include <QByteArray>
#include <QStringList>

#include <eirBase/MultiName.h>

class HexDump
{
public:
    HexDump();
    HexDump(const void * data, const int bytes,
            const MultiName &name=MultiName());
    HexDump(const QByteArray &ba,
            const MultiName &name=MultiName());
    void format();
    QStringList strings() const;
    QString string(const QChar &joinChar=QChar('\n'));

private:
    const qptrdiff * cmpData=nullptr;
    const int cmBytes=0;
    const MultiName cmName;
    QStringList mStrings;
};

