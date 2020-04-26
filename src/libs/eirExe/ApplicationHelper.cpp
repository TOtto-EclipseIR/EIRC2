// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>
#include <eirBase/Milliseconds.h>
//#include <eirBase/Uid.h>

#include "CommandLine.h"
#include "Settings.h"

#include "../../../VERSION.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , mpTempDir(new QTemporaryDir())
    , mpCommandLine(new CommandLine(parent))
{
    TRACEFN
    setObjectName("Application");
    TSTALLOC(mpTempDir);
    TSTALLOC(mpCommandLine);
    EXPECT(mpTempDir->isValid())
    CONNECT(mpCommandLine, &CommandLine::processComplete,
            this, &ApplicationHelper::commamdLineScanned);
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

CommandLine *ApplicationHelper::commandLine()
{
    return mpCommandLine;
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
    TSTALLOC(mpCommandLine);
    QTimer::singleShot(100, this, &ApplicationHelper::initSettings);
}

void ApplicationHelper::initSettings()
{
    TRACEFN

    TSTALLOC(mpCommandLine)
    if ( ! mpCommandLine->orgName().isNull())
         qApp->setOrganizationName(mpCommandLine->orgName());
    if ( ! mpCommandLine->appName().isNull())
         qApp->setApplicationName(mpCommandLine->appName());

    mpSettings = new Settings(this);
    TSTALLOC(mpSettings);
    WANTDO("Take the smell out");

    emit initFinished();
}

void ApplicationHelper::commamdLineScanned()
{

}
