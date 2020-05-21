// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QFile>
#include <QTemporaryDir>

#include <eirBase/Var.h>
class CommandLine;
class ConfigObject;
class ErrorHandler;
class Settings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
    QFile * tempFile(const QString &ext,
                     QObject * parent=nullptr);
    CommandLine * commandLine() const;
    ConfigObject *config() const;

public slots:
    void run();

protected:

public slots:
    void initCommandLine();
    void initSettings();
    void commamdLineScanned();

public: // static

signals:
    void initFinished();
    void scanComplete();

private:
    QTemporaryDir * mpTempDir=nullptr;
    Settings * mpSettings=nullptr;
    QList<QFile *> mTempFiles;
};

