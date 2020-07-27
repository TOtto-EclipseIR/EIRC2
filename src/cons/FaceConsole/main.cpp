#include <QCoreApplication>

#include"FaceConsole.h"

#include "../../version.h"

#include <QtGlobal>
#include <QtDebug>
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTimer>

#if 0
const char * contextStartFile = "main.cpp";
const int contextStartLine = 8541;
const char * contextStartFunction = "startFileName";

void myStartFileMessageHandler(QtMsgType qmt,
                               const QMessageLogContext &qmlc,
                               const QString &message)
{
    static QFile startFile;
    static QTextStream textStream((QIODevice *)(&startFile));

    if (QtInfoMsg == qmt
            && contextStartFile == qmlc.file
            && contextStartLine == qmlc.line
            && contextStartFunction == qmlc.function)
    {
        startFile.setFileName(qmlc.category);
        startFile.open(QIODevice::WriteOnly | QIODevice::Text);
    }
    else
    {
        textStream << message << Qt::endl;
    }
}

void installFileMessageHandler(char * exeFileString)
{
    QFileInfo exeFileInfo(exeFileString);
    QDir startDir = exeFileInfo.dir();
    startDir.mkpath("log");
    startDir.cd("log");
    qInstallMessageHandler(myStartFileMessageHandler);
    QDateTime startTimestamp = FaceConsole::baseDateTime();
    QString startFileName(exeFileInfo.completeBaseName()
                          +"-Start"
                          + (startTimestamp.toString("ddhhmm"))
                          +".txt");    startDir.mkpath("log");
    QMessageLogContext context(contextStartFile, contextStartLine,
                               contextStartFunction,
                               startFileName.toLocal8Bit());
    QMessageLogger("main.cpp", -8541, "startFileName",
                   startFileName.toLocal8Bit()).info("START");
}
#endif

int main(int argc, char *argv[])
{
//    installFileMessageHandler(argv[0]);

    QCoreApplication a(argc, argv);
    a.setApplicationName("FaceConsole");
    a.setApplicationVersion(EIRC2_VER_STRING " " EIRC2_VER_TRUNKNAME);
    a.setOrganizationName(EIRC2_VER_ORGNAME);

    FaceConsole c(a.parent());
    Q_UNUSED(c);

    return a.exec();
}
