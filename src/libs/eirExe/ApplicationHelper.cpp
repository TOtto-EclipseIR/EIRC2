// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.cpp
#include "ApplicationHelper.h"

#include <QTimer>

#include <eirBase/Debug.h>
#include <eirBase/ErrorHandler.h>
#include <eirBase/Milliseconds.h>
#include <eirBase/Uid.h>

#include "CommandLine.h"
#include "Settings.h"

ApplicationHelper::ApplicationHelper(QObject *parent)
    : QObject(parent)
    , mpTempDir(new QTemporaryDir())
{
    TRACEFN
    setObjectName("Application");
    TSTALLOC(mpTempDir);
    EXPECT(mpTempDir->isValid())
    TSTALLOC(mpSettings);
}
/*
ApplicationHelper::~ApplicationHelper()
{
    foreach (QFile * pTempFile, mTempFiles)
        if (pTempFile) delete pTempFile;
    if (mpTempDir) delete mpTempDir;
}
*/
QFile *ApplicationHelper::tempFile(const QString &ext,
                                   QObject *parent)
{
    QString fileBaseName = Uid::create().toString();
    QFile * f = new QFile(parent ? parent : this);
    TSTALLOC(f);
    f->setFileName(mpTempDir->filePath(fileBaseName + ext));
    // Returning a closed, unique QFile pointer.
    // The developer can open them as the apps need,
    // but is not responsible for deleting the file.
    mTempFiles.append(f);
    return f;
}

void ApplicationHelper::run()
{
    TRACEFN
    QTimer::singleShot(100, this, &ApplicationHelper::initSettings);
}

void ApplicationHelper::initSettings()
{
    TRACEFN
    mpSettings = new Settings(this);
    TSTALLOC(mpSettings);
    QTimer::singleShot(100, this,
                     &ApplicationHelper::initCommandLine);
}

void ApplicationHelper::initCommandLine()
{
    TRACEFN
    mpCommandLine = new CommandLine(this);
    TSTALLOC(mpCommandLine);
    emit initFinished();
}

