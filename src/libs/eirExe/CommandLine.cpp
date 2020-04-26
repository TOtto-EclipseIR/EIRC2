// file: {repo: EIRC2}./src/libs/eirExe/CommandLine.cpp
#include "CommandLine.h"

#include <eirBase/Debug.h>


CommandLine::CommandLine(QObject *parent)
    : QObject(parent)
    , cmArguments(qApp->arguments())
{
    TRACEQFI << cmArguments;
    setObjectName("CommandLine");

    mExeFileInfo.setFile(cmArguments.first());
    mArgIndex = 1;
    if (cmArguments.size() > mArgIndex)
        mFirstArgument = cmArguments.at(mArgIndex++);
    process();
    emit processComplete();
}

QString CommandLine::orgName() const
{
    return  mOrgName;
}

QString CommandLine::appName() const
{
    return mAppName;
}

QFileInfoList CommandLine::argumentInfoList() const
{
    return mArgumentsInfo;
}

void CommandLine::process()
{
    if (mFirstArgument.startsWith(QChar('%'))
             || mFirstArgument.startsWith('_'))
    {
        int x = mFirstArgument.indexOf(QChar('/'));
        if (x < 0)
            mAppName = mFirstArgument.mid(1);
        else
        {
            mOrgName = mFirstArgument.mid(1, x-1);
            mAppName = mFirstArgument.mid(x+1);
        }
    }
    TODO("MS02~03 mSettings");
    while (mArgIndex < qApp->arguments().size())
        mArgumentsInfo << QFileInfo(qApp->arguments()
                                    .at(mArgIndex++));
}
