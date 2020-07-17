#pragma once

#include <eirBase/VarPak.h>

class ConfigPak : public VarPak
{
public:
    ConfigPak(const Id &id);
    ConfigPak(const MultiName &groupName);

private:
    const MultiName cmGroupName;
};

