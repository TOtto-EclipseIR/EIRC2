#include "Configurations.h"

#include <eirBase/Debug.h>

Configurations::Configurations()
{

}

void Configurations::setDefaults()
{
    VarMap objdetMap;
    VarMap haarMap;
    VarMap frontalMap;

    objdetMap << Var("DetectorDir", "../Detectors");

    //haarMap.insert(objdetMap);

    //frontalMap.insert(haarMap);
    frontalMap << Var("FileName", "DefaultFrontalFace.xml");

//    mNamedConfigMaps.insert(BasicName("ObjDet"), objdetMap);
  //  mNamedConfigMaps.insert("Haar", haarMap);
    //mNamedConfigMaps.insert("FrontalFace", frontalMap);
}

void Configurations::setOveride()
{
    TODO(KISS);
}

void Configurations::insert(const BasicName &name,
                            const VarMap &map)
{
    foreach (Var var, map.values())
    {
        MultiName newName = var.name();
        newName.prependName(name);
        Var newVar = var;
        newVar.set(newName);
        //insert(newName.sortable(), newVar);
    }
}
/*
void Configurations::insert(const Var &var,
                            BasicName &groupName)
{
    mNamedConfigMaps.insert(var.name()
                            .prependName(groupName), var);

}
*/
