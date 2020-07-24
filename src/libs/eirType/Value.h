#pragma once

#include <QVariant>

class Value : public QVariant
{
public:
    Value(const QVariant &variant);
};

