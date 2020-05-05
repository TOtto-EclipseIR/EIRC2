// file: {EIRC2 Repo}./src/libs/eirExe/CmdLineObject.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <eirBase/MultiName.h>
#include <eirBase/Var.h>
#include <eirBase/VarMap.h>
#include <eirType/Sortable.h>

class EIREXE_EXPORT CmdLineObject : public QObject
{
    Q_OBJECT
public:
    class CommandLineArgument
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
    NullFlag = 0,
    EnableHelp = 0x01,
    EnableVersion = 0x02,
};
Q_DECLARE_FLAGS(Options, Option);

public:
    explicit CmdLineObject(QObject *parent = nullptr);


public slots:
    void addOption(const MultiName & name,
                   const QCommandLineOption & option);
    void addPositionalArgument(const MultiName &name,
                               const bool takeAll=false);
    void addPositionalArgument(const CommandLineArgument &arg,
                               const bool takeAll=false);
    void addHelpOption();
    void addVersionOption();

    void process();

protected slots:
    void setupApplicationValues();
    void processAddOptions();

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
    Options mOptions=0;
    Var::List mApplicationValues;
    QMap<Sortable, QCommandLineOption> mOptionMap;
    QList<CommandLineArgument *> mArguments;
    // processing
    QCommandLineParser mParser;
    QString mOrgName;
    QString mAppName;
    // results
    Var::List mPositionalArgumentResult;
    VarMap mOptionValues;
    VarMap mSettings;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CmdLineObject::Options)
