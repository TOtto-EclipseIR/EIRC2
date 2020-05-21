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

#include "../../version.h"

class EIREXE_EXPORT CommandLine : public QObject
{
    Q_OBJECT
public:
#ifdef EIRC2_IF2CONSOLE_TAKETWO23
#else
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
#endif
#ifdef EIRC2_IF2CONSOLE_TAKETWO23
public:
    explicit CommandLine(QObject *parent = nullptr);
    QFileInfoList positionalFileInfoList() const;
    const QStringList exeArguments() const;
    Configuration configuration() const;

protected:
    void parseConfigArgument(const QString &arg);
    QStringList readTxtFileArguments(const QString &arg);

protected slots:
    void processFourthPass();
    void processFifthPass();
    void processSixthPass();

#else
    CommandLineMachine * machine() const;

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
#endif
    //    CommandLineMachine * const cmpMachine=nullptr;
#ifdef EIRC2_IF2CONSOLE_TAKETWO23
private:
    // inputs
    const QStringList cmExeArgumentList;
    QStringList mFifthPassArguments;
    QStringList mSixthPassArguments;
    QFileInfoList mPositionalFileDirInfoList;
    Configuration mConfiguration;
#else
    Options mOptions=0;
    // processing
    QStringList mThirdPassArguments;
    QCommandLineParser mParser;
    QString mOrgName;
    QString mAppName;
    // results
    Var::List mPositionalArgumentResult;
    VarMap mOptionValues;
#endif
};
#ifdef EIRC2_IF2CONSOLE_TAKETWO23
#else
Q_DECLARE_OPERATORS_FOR_FLAGS(CommandLine::Options)
#endif
