// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QFile>
#include <QTemporaryDir>

#include <eirBase/Var.h>
class CommandLine;
class CommandLineClientInterface;
class ConfigObject;
class ErrorHandler;
class LegacySettings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
    void set(CommandLineClientInterface const * client) const;
    QFile * tempFile(const QString &ext,
                     QObject * parent=nullptr);
    const CommandLine *commandLine() const;
    CommandLine &rCommandLine();
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
    LegacySettings * mpSettings=nullptr;
    CommandLine * const cmpCommandLine=nullptr;
    QList<QFile *> mTempFiles;
};

