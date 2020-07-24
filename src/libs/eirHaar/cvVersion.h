//! \file cvVersion.h
#pragma once
#include "eirHaar.h"

#include<QString>

#include <eirType/VersionInfo.h>

class EIRHAAR_EXPORT cvVersion : public VersionInfo
{
public:
    cvVersion();
    QString toString() const;
    operator QString () const;
    QString operator ()() const;
};

