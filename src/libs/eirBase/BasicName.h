#pragma once
#include "eirBase.h"

#include <QByteArray>
#include <QList>
#include <QString>
#include <QVariant>

class EIRBASE_EXPORT BasicName
{
public:
    typedef QByteArray Sortable;
    typedef QList<BasicName> List;

public:
    BasicName(void);
    BasicName(const QString & sNname);
    BasicName(const char * cName);
    BasicName(const QByteArray & baName);
    void set(const QString & name);
    QString toString(void) const;
    QByteArray toByteArray() const;
    operator QString (void) const;
    QString operator () (void) const;
    QVariant toVariant(void) const;
    operator QVariant (void) const;
    Sortable sortable(void) const;
    bool operator == (const BasicName & other) const;
    bool operator != (const BasicName & other) const;
    bool operator <  (const BasicName & other) const;
    bool UnitTest(void);

public: // static
    static QStringList toStringList(BasicName::List basicList);

private:
    QString mName;
};
