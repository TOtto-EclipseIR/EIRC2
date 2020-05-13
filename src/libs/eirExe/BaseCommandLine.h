// file: {EIRC2 Repo}./src/libs/eirExe/BaseCommandLine.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileInfoList>

#include <eirBase/MultiName.h>
#include <eirBase/Var.h>
#include <eirBase/VarMap.h>
#include <eirType/Sortable.h>

class EIREXE_EXPORT BaseCommandLine : public QObject
{
    Q_OBJECT
public:
    class EIREXE_EXPORT CommandLineArgument
    {
    public:
        CommandLineArgument(const MultiName & name);
        CommandLineArgument(const MultiName & name,
                            const QString & argument,
                            const QString &description=QString(),
                            const QString &syntax=QString());
        MultiName name() const;
        QString argument() const;
        QString description() const;
        QString syntax() const;
        void setTakeAll(bool yes=true);

    private:
        const MultiName cmName;
        const QString cmArgument;
        const QString cmDescription;
        const QString cmSyntax;
        bool mTakeAll=false;
    };

enum Option
{
    NullOptions = 0,
    EnableHelp                  = 0x01,
    EnableVersion               = 0x02,
    EnableSettingValues         = 0x0100,
    EnableSettingsOrgApp        = 0x0200,
    EnableFileImportTXT         = 0x00010000,
    EnableFileImportJSON        = 0x00020000,
    EnableFileImportINI         = 0x00040000,
    EnableFileImportXML         = 0x00080000,

};
Q_DECLARE_FLAGS(Options, Option);

public:
    explicit BaseCommandLine(QObject *parent = nullptr);
    QFileInfoList positionalFileInfoList() const;


public slots:
    void addOption(const MultiName & name,
                   const QCommandLineOption & option);
    void addPositionalArgument(const MultiName &name,
                               const bool takeAll=false);
    void addPositionalArgument(const CommandLineArgument &arg,
                               const bool takeAll=false);
    void addHelpOption();
    void addVersionOption();
    Options &rwrefOptions();


    virtual void setupApplicationValues();
    virtual void setupSettings();
    virtual void setupArguments();
    virtual void setup() = 0;
    void process();

protected slots:
    void processAddOptions();
    void processAddArguments();
    void processSecondPass();
    void processThirdPass();
    void processFourthPass();
    virtual void handleAmpersandArgument(const QString &arg);
    virtual void handleBangArgument(const QString &arg);
    virtual void handlePercentArgument(const QString &arg);
    virtual void handlePositionalArguments();
    virtual void handlePositionalFileDir(const QString &arg);

signals:
    void constructed(void);
    void applicationValueSet(MultiName key, QString value);
    void applicationValuesSet();
    void optionSet(MultiName name);
    void argumentSet(int position, MultiName name);
    void processingStarted();
    void processingValueAdded(MultiName name, QString value);
    void processingOptionAdded(QCommandLineOption option);
    void processingFinished();

public:
    const MultiName helpOptionName=MultiName("QtOption/Help");
    const MultiName versionOptionName=MultiName("QtOption/Version");

private:
    // inputs
    const QStringList cmExeArgumentList;
    Options mOptions=0;
    Var::List mApplicationValues;
    QMap<Sortable, QCommandLineOption> mOptionMap;
    QList<CommandLineArgument *> mArguments;
    // processing
    QCommandLineParser mParser;
    QStringList mThirdPassArguments;
    QString mOrgName;
    QString mAppName;
    // results
    Var::List mPositionalArgumentResult;
    QFileInfoList mPositionalFileDirInfoList;
    VarMap mOptionValues;
    VarMap mConfiguration;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(BaseCommandLine::Options)
