// file: {repo: EIRC2}./src/libs/eirExe/Settings.cpp
#include "LegacySettings.h"

#include <QTimer>

#include <eirBase/Debug.h>

#include "ApplicationHelper.h"

LegacySettings::LegacySettings(ApplicationHelper *parent)
    : QSettings(parent)
    , mpHelper(parent)
{
    TRACEFN
    setObjectName("Settings");
}

ApplicationHelper * LegacySettings::helper()
{
    return mpHelper;
}
