#include "FinderCascade.h"

FinderCascade::FinderCascade(const CascadeType &cascadeType,
                             ConfigObject *configObject)
    : mCascade(cvCascade(cascadeType))
    , cmpCfgObj(configObject)
{

}
