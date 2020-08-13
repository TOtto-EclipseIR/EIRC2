#pragma once
#include "eirXfr.h"

#include <QtGlobal>
#include <QtDebug>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>


class EIRXFR_EXPORT StartupDebug
{
public:
    StartupDebug(const QString &exeArg0);
    void finish();

protected:
    bool start();

private:
    const QString cmExeArg0;
    QFileInfo const cmExeFileInfo;
    QFile * const cmpStartupFile;
    const QtMessageHandler cmMyHandler=&myStartupMessageHandler;
    QString mStartupFileName;

protected: // static
    static void myStartupMessageHandler(QtMsgType type,
             const QMessageLogContext &context,
             const QString &msg);

private: // static
    static QTextStream * smpTextStream;
};
//Q_GLOBAL_STATIC(StartupDebug, slog);



