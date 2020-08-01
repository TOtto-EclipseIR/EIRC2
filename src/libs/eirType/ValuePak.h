// file: {repo: EIRC2}./src/libs/eirType/ValuePak.h
#pragma once
#include "eirType.h"

#include <QList>
#include <QMap>
#include <QStack>

#include "Id.h"
#include "MultiName.h"
#include "Value.h"

class ValuePak
{
public:
    ValuePak();
    ValuePak(const Id id=Id());
    void set(const Id &id);
    void set(const QByteArray &byteArray);
    void set(const Value::List &varList);
    void insert(const Value::Map &valueMap);
    void set(const int index, const Value &listItem);
    void append(const Value &listItem);
    void insert(const Value &mapItem);
    void insert(const MultiName &key,
                const QVariant &value);
    Value &at(const MultiName &name); // non-const
    Value at(const MultiName &name) const;
    QVariant value(const MultiName &name) const;
    Id id() const;
    Id &id();
    QByteArray bytes() const;
    Value::List list() const;
    Value::List & list(); // non-const
    Value::Map map() const;
    Value::Map & map(); // non-const
    Value &operator[](const MultiName &name); // non-const
    Value operator[](const MultiName &name) const;
    QVariant operator()(const MultiName &name) const;

private:
    Id mId;
    QByteArray mBA;
    Var::List mVarList;
    Value::Map mVarMap;
};

