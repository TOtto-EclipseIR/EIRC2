// file: {repo: EIRC2}./src/libs/eirExe/Settings.cpp
#include "LegacySettings.h"

#include <QTimer>

#include <eirBase/Debug.h>

#include "ApplicationHelper.h"

Settings::Settings(ApplicationHelper *parent)
    : QSettings(parent)
    , mpHelper(parent)
{
    TRACEFN
    setObjectName("Settings");
}

ApplicationHelper * Settings::helper()
{
    return mpHelper;
}
