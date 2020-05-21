// file: {EIRC2 Repo}./src/libs/eirExe/CommandLine.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileInfoList>
#include <QStateMachine>

#include <eirBase/MultiName.h>
#include <eirBase/Var.h>
#include <eirBase/VarMap.h>
#include <eirType/Sortable.h>

#include "Configuration.h"
//class CommandLineMachine;

class EIREXE_EXPORT CommandLine : public QObject
{
    Q_OBJECT
public:
    enum Option
    {
        NullOptions = 0,
        DisableHelp                 = 0x01,
        DisableVersion              = 0x02,
        EnableSettingValues         = 0x0100,
        EnableSettingsOrgApp        = 0x0200,
        EnableFileImportTXT         = 0x00010000,
        EnableFileImportJSON        = 0x00020000,
        EnableFileImportINI         = 0x00040000,
        EnableFileImportXML         = 0x00080000,

    }; // enum Option
    Q_DECLARE_FLAGS(Options, Option);

public:
    explicit CommandLine(QObject *parent = nullptr);
 //   CommandLineMachine * machine() const;
    QFileInfoList positionalFileInfoList() const;
    const QStringList exeArguments() const;
    Configuration configuration() const;

protected:
    void parseConfigArgument(const QString &arg);
    QStringList readTxtFileArguments(const QString &arg);

public slots:
    void addOption(const QCommandLineOption & option);
    void addPositionalArgument(const MultiName &name,
                               const QString &desc=QString(),
                               const QString &syntax=QString());
    void noHelpOption();
    void noVersionOption();
    Options &rwrefOptions();


    virtual void setupApplicationValues();
    virtual void setupSettings();
    virtual void setupArguments();
    void process();

protected slots:
    void processSecondPass();
    void processThirdPass();
    void processFourthPass();
    void processFifthPass();
    void processSixthPass();
    virtual void setup() = 0;
    virtual void handleAmpersandArgument(const QString &arg);
    virtual void handleBangArgument(const QString &arg);
    virtual void handlePercentArgument(const QString &arg);
    virtual void handlePositionalArguments();
    virtual void handlePositionalFileDir(const QString &arg);

signals:
    void constructed(void);
    void applicationValueSet(MultiName key, QString value);
    void applicationValuesSet();
    void optionSet(QString name);
    void argumentSet(int position, MultiName name);
    void processingStarted();
    void processingValueAdded(MultiName name, QString value);
    void processingOptionAdded(QCommandLineOption option);
    void processingFinished();

public:
    const MultiName helpOptionName=MultiName("QtOption/Help");
    const MultiName versionOptionName=MultiName("QtOption/Version");

private:
//    CommandLineMachine * const cmpMachine=nullptr;
    // inputs
    const QStringList cmExeArgumentList;
    Options mOptions=0;
    // processing
    QCommandLineParser mParser;
    QStringList mThirdPassArguments;
    QStringList mFifthPassArguments;
    QStringList mSixthPassArguments;
    QString mOrgName;
    QString mAppName;
    // results
    Var::List mPositionalArgumentResult;
    QFileInfoList mPositionalFileDirInfoList;
    VarMap mOptionValues;
    Configuration mConfiguration;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CommandLine::Options)
