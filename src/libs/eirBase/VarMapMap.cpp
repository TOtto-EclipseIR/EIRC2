#include "VarMapMap.h"

VarMapMap::VarMapMap()
{

}

VarMap VarMapMap::value(const MultiName &name) const
{
    return VarMap::Map::value(name.sortable());
}
