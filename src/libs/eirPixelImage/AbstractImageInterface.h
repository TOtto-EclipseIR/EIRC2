#pragma once

#include <QBitArray>

class AbstractImageInterface
{
public:
    AbstractImageInterface();
    virtual QBitArray capabilities() const = 0;
};

