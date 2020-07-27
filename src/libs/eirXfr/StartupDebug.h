#pragma once

#include <QtGlobal>
#include <QtDebug>
#include <QByteArray>
#include <QFile>
#include <QTextStream>


class StartupDebug
{
public:
    StartupDebug();

protected:
    void myBufferedMessageHandler(QtMsgType qmt,
                                  const QMessageLogContext &qmlc,
                                  const QString &message);
    void (QtMsgType qmt,
                                  const QMessageLogContext &qmlc,
                                  const QString &message);

private:
};



