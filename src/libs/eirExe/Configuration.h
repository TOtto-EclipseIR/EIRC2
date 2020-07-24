#pragma once
#include "eirExe.h"

#include <eirType/VarMap.h>


class EIREXE_EXPORT Configuration : public VarMap
{
public:
    Configuration();
    Configuration(const VarMap &other);

    QString string(const MultiName &key,
                   const QString &defValue=QString());
    signed signedInt(const MultiName &key,
                   const signed &defValue=0);
};

