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
    MultiName(const BasicName &segment);
    MultiName(const BasicName::List & other);
    MultiName(const QStringList & qslNames);
    MultiName(const MultiName &base, const MultiName &name);
    bool isEmpty(void) const;
    void clear(void);
    void set(const QString & qsNames);
    void set(const QStringList & qslNames);
    void prependName(const MultiName &groupName);
    MultiName prepended(const MultiName &groupName) const;
    BasicName firstSegment() const;
    BasicName segmentAt(const int index) const;
    bool startsWith(const MultiName &groupName) const;
    int segmentCount() const;
    void removeFirstSegments(int count);
    void removeLastSegment();
    MultiName firstSegmentsRemoved(int count) const;
    QStringList toStringList(void) const;
    QString toString(void) const;
    operator QString (void) const;
    QString operator () (void) const;
    QVariant toVariant(void) const;
    operator QVariant (void) const;
    QString sortable(void) const;
    uint hash() const;
    bool operator == (const MultiName & other) const;
    bool operator <  (const MultiName & other) const;
    void dump() const;

protected:
    QString join(const QChar & delimiter) const;

protected: // static
    static QChar getDelimiter(void);
    static void setDelimiter(const QChar & value);

private:
    BasicName::List mBasicSegmentNames;

private: // static
    static const uint scmHashSeed;
    static QChar smDelimiter;
};

