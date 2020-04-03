#include "Configurations.h"

Configurations::Configurations()
{

}

void Configurations::setDefaults()
{
    VarMap objdetMap;
    VarMap haarMap;
    VarMap frontalMap;

    objdetMap << Var("DirName", "../Detectors");

    haarMap.insert(objdetMap);

    frontalMap.insert(haarMap);
    frontalMap << Var("FileName", "DefaultFrontalFace.xml");

    mNamedConfigMaps.insert("ObjDet", objdetMap);
    mNamedConfigMaps.insert("Haar", haarMap);
    mNamedConfigMaps.insert("FrontalFace", frontalMap);
}
