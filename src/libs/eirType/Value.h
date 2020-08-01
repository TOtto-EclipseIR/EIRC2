#pragma once

#include <QList>
#include <QMap>
#include <QPair>
#include <QVariant>
#include "MultiName.h"


class Value : public QPair<MultiName, QVariant>
{
public:
    typedef QList<Value> List;
    typedef QMap<MultiName, QVariant> Map;

public:
    Value();
    Value(const MultiName &name,
          const QVariant &variant=QVariant());
    Value(const MultiName &name,
          const QVariant::Type vtype);
};

