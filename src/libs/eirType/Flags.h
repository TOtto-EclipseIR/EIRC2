//! \file BaseImageQueue.h
#pragma once
#include "eirType.h"

#include <QBitArray>
#include <QChar>
#include <QList>
#include <QString>

#include  <eirBase/BasicName.h>

#include "DualMap.h"


class EIRTYPE_EXPORT Flags
{
public:
    Flags(const int size=0, const bool is=false);
    // status
    int size() const;
    void clear();
    void resize(const int newSize, const bool truncate=false);
    void fill(const bool is=true);
    bool isAll(const bool is) const;
    bool isAllUnset() const;
    bool isAllSet() const;
    bool contains(const int index) const;
    bool contains(const BasicName & name) const;
    bool at(const int index) const;
    bool at(const BasicName &name) const;
    bool operator [] (const int index) const;
    bool operator [] (const BasicName &name) const;
    // manipulation
    QBitRef bitRef(const int index);
    QBitRef bitRef(const BasicName &name);
    void unset(const int index);
    void unset(const BasicName &name);
    void unsetAll();
    void set(const int index, const bool is=true);
    void set(const BasicName &name, const bool is=true);
    void setAll();
    // setup
    int registerFlag(const BasicName &name);
    BasicName name(const int index) const;
    const char *namePch(const int index) const;
    int index(const BasicName &name) const;
    BasicName::List names() const;
    BasicName::List namesSet() const;
    QString namesSetString(const QChar delimeter=QChar(' '));
    QList<int> indiciesSet() const;

private:
    QBitArray mBits;
    DualMap<int, BasicName> mIndexNameDMap;
};

