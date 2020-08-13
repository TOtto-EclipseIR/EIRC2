// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QDateTime>
#include <QFile>
#include <QTemporaryDir>

#include <eirType/Var.h>
#include <eirType/VersionInfo.h>
class ErrorHandler;

//#include "BaseArgumentManager.h"
class CommandLine;
class CommandLineClientInterface;
class ConfigObject;
class LegacySettings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
    VersionInfo version() const;
    void set(CommandLineClientInterface const * client) const;
    void set(const VersionInfo & verInfo);
    QFile * tempFile(const QString &ext,
                     QObject * parent=nullptr);
    const CommandLine *commandLine() const;
    CommandLine &rCommandLine();
    ConfigObject *config() const;

public: // static
    static QDateTime baseDateTime();

public slots:
    void run();

protected:

public slots:
    void initCommandLine();
    void initSettings();
    void commamdLineScanned();

signals:
    void initFinished();
    void scanComplete();

private:
    VersionInfo cmVerInfo;
//    ArgumentList mArguments;
    LegacySettings * mpSettings=nullptr;
    CommandLine * const cmpCommandLine=nullptr;
    ConfigObject * const cmpConfigObject=nullptr;
    QTemporaryDir const * cmpTempDir=nullptr;
    QList<QFile *> mTempFiles;

private: // static
    static QDateTime smBaseDateTime;
};

