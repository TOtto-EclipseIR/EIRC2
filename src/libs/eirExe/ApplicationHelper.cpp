// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>
#include <eirBase/Milliseconds.h>
//#include <eirBase/Uid.h>

#include "CommandLine.h"
#include "LegacySettings.h"

#include "../../version.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , mpTempDir(new QTemporaryDir())
{
    TRACEFN
    setObjectName("Application");
    TSTALLOC(mpTempDir);
    EXPECT(mpTempDir->isValid())
}

QFile *ApplicationHelper::tempFile(const QString &ext,
                                   QObject *parent)
{
    //QString fileBaseName = Uid::create().toString();
    QString fileBaseName = Milliseconds::current()
            .toByteArray().toHex();
    QFile * f = new QFile(parent ? parent : this);
    TSTALLOC(f);
    f->setFileName(mpTempDir->filePath(fileBaseName + ext));
    // Returning a closed, unique QFile pointer.
    // The developer can open them as the apps need,
    // but is not responsible for deleting the file.
    mTempFiles.append(f);
    return f;
}

CommandLine *ApplicationHelper::commandLine() const
{

}

ConfigObject *ApplicationHelper::config() const
{

}

void ApplicationHelper::run()
{
    TRACEFN
    qApp->setOrganizationName(EIRC2_VER_ORGNAME);
    qApp->setApplicationName("If2Console");
    qApp->setApplicationVersion(EIRC2_VER_APPVER);
    QTimer::singleShot(100, this, &ApplicationHelper::initCommandLine);
}

void ApplicationHelper::initCommandLine()
{
    TRACEFN
    QTimer::singleShot(100, this, &ApplicationHelper::initSettings);
}

void ApplicationHelper::initSettings()
{
    TRACEFN

#if 1
    MUSTDO(OrgName AppName)
#else
    if ( ! mpCmdLineObject->orgName().isNull())
         qApp->setOrganizationName(mpCmdLineObject->orgName());
    if ( ! mpCmdLineObject->appName().isNull())
         qApp->setApplicationName(mpCmdLineObject->appName());
#endif
    mpSettings = new Settings(this);
    TSTALLOC(mpSettings);
    WANTDO("Take the smell out");

    emit initFinished();
}

void ApplicationHelper::commamdLineScanned()
{
    TRACEFN
    NEEDDO(it);
}
