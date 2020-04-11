#include "VarMapMap.h"

#include "Debug.h"

VarMapMap::VarMapMap()
{

}

VarMap VarMapMap::value(const MultiName &name) const
{
    NEEDUSE(name); NEEDFNR(VarMap());
//    return VarMap::Map::value(name.sortable());
}
