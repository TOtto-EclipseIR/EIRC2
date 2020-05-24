#pragma once

#include <eirBase/VarMap.h>


class Configuration : public VarMap
{
public:
    Configuration();
    Configuration(const VarMap &other);
};

