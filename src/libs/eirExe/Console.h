#pragma once
#include "eirExe.h"

#include <QObject>
#include "ApplicationHelper.h"

#include <QCoreApplication>

class QFile;

class CommandLine;


class EIREXE_EXPORT Console : public ApplicationHelper
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);
    CommandLine * commandLine();

public slots:
    void writeLine(const QString &qs,
                   const bool andFlush=true);
    void writeLines(const QStringList &qsl);
    void writeErr(const QString &qs,
                  const bool andFlush=true);
    void writeErrs(const QStringList &qsl);
    void commandLineComplete();

signals:
    void commandLineScanned();

private:
    QCoreApplication * mpCoreApp=nullptr;
    QFile * mpIn=nullptr;
    QFile * mpOut=nullptr;
    QFile * mpErr=nullptr;
};

