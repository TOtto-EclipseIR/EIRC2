// file: {repo: EIRC2}./src/libs/eirExe/CommandLine.cpp
#include "CommandLine.h"

#include <QFileInfo>

#include <eirBase/Debug.h>


CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
    , cmExeArguments(qApp->arguments())
{
    TRACEQFI << cmExeArguments;
    setObjectName("CommandLine");
}

QString CommandLine::orgName() const
{
    return  mOrgName;
}

QString CommandLine::appName() const
{
    return mAppName;
}

QFileInfoList CommandLine::fileArgumentInfoList() const
{
    TRACEQFI << "mArgumentsInfo.size()" << mFileArgumentsInfo.size();
    return mFileArgumentsInfo;
}

void CommandLine::process()
{
    TRACEQFI << qApp->arguments();
/*
    mExeFileInfo.setFile(cmArguments.first());
    mArgIndex = 1;
    if (cmArguments.size() > mArgIndex)
        mFirstArgument = cmArguments.at(mArgIndex++);
    process();
    emit processComplete();
*/
    WANTDO(Parser::parse())
    mParsedArguments = cmExeArguments;
    mExeFileInfo = QFileInfo(mParsedArguments.takeFirst());
    foreach (QString arg, mParsedArguments)
    {
        if (arg.startsWith(QChar('%'))
                 || arg.startsWith('_'))
        {
            int x = arg.indexOf(QChar('/'));
            if (x < 0)
                mAppName = arg.mid(1);
            else
            {
                mOrgName = arg.mid(1, x-1);
                mAppName = arg.mid(x+1);
            }
        }
        else
        {
            mPositionalArguments << arg;
            QFileInfo qfi(arg);
            if (qfi.isFile() || qfi.isDir())
                mFileArgumentsInfo << qfi;
            else
                mFileArgumentsInfo << QString();
        }
    }

    if (mOrgName.notEmpty())
        qApp->setOrganizationName(mOrgName);
    if (mAppName.notEmpty())
        qApp->setApplicationName(mAppName);
            /*
    TODO("MS02~03 mSettings");
    while (mArgIndex < qApp->arguments().size())
        mFileArgumentsInfo << QFileInfo(qApp->arguments()
                                    .at(mArgIndex++));
*/
    TRACE << mFileArgumentsInfo;
}
