// file: ./libs/eirBase/MultiName.h
#pragma once
#include "eirBase.h"

#include <QByteArray>
#include <QChar>
#include <QList>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "BasicName.h"


class EIRBASE_EXPORT MultiName
{
public:
    typedef QList<MultiName> List;

public:
    MultiName(void);
    MultiName(const QString & stringNames);
    MultiName(char * cNames);
    MultiName(const QByteArray & baNames);
    MultiName(const BasicName::List & other);
    MultiName(const QStringList & qslNames);
    MultiName(const MultiName &base, const MultiName &name);
    bool isEmpty(void) const;
    void clear(void);
    void set(const QString & qsNames);
    void set(const QStringList & qslNames);
    BasicName first() const;
    void removeLast();
    QStringList toStringList(void) const;
    QString toString(void) const;
    operator QString (void) const;
    QString operator () (void) const;
    QVariant toVariant(void) const;
    operator QVariant (void) const;
    QString sortable(void) const;
    bool operator == (const MultiName & other) const;
    bool operator <  (const MultiName & other) const;
    void dump() const;

protected:
    QString join(const QChar & delimiter) const;

protected: // static
    static QChar getDelimiter(void);
    static void setDelimiter(const QChar & value);

private:
    BasicName::List mBasicNames;

private: // static
    static QChar smDelimiter;
};

