#include "StartupDebug.h"

#include <QCoreApplication>
#include <QIODevice>

QTextStream * StartupDebug::smpTextStream=nullptr;

StartupDebug::StartupDebug(const QString &exeArg0)
    : cmExeArg0(exeArg0)
    , cmExeFileInfo(QFileInfo(cmExeArg0))
    , cmpStartupFile(new QFile(qApp->parent()))
{
    start();
}

void StartupDebug::finish()
{
    qInstallMessageHandler(0);
    delete smpTextStream;
    smpTextStream = nullptr;
    cmpStartupFile->close();

}

bool StartupDebug::start()
{
    mStartupFileName = QString("./%1-StartLog.txt")
            .arg(cmExeFileInfo.completeBaseName());
    cmpStartupFile->setFileName(mStartupFileName);
    cmpStartupFile->open(QIODevice::WriteOnly
                         | QIODevice::Text
                         | QIODevice::Truncate);
    if (cmpStartupFile->isWritable())
    {
        smpTextStream = new QTextStream(cmpStartupFile);
        qInstallMessageHandler(myStartupMessageHandler);
    }  // else stay with stderr
    return nullptr != smpTextStream;
}

void StartupDebug::myStartupMessageHandler(QtMsgType type,
               const QMessageLogContext &context,
               const QString &msg)
{
    Q_ASSERT_X(nullptr != smpTextStream,
               "StartupDebug::myStartupMessageHandler",
               "static QTextStream * smpTextStream");
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function
                         ? context.function : "";
    Q_UNUSED(localMsg); Q_UNUSED(file); Q_UNUSED(function);

    switch (type)
    {
    case QtDebugMsg:
    case QtInfoMsg:
    case QtWarningMsg:
    case QtCriticalMsg:
    case QtFatalMsg:
        *smpTextStream << msg << Qt::endl;
        smpTextStream->flush();
        break;
    }
}
