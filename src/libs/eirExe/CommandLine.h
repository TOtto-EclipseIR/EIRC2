// file: {repo: EIRC2}./src/libs/eirExe/Settings.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QJsonObject>
#include <QSettings>
#include <QUrl>

#include <eirBase/BasicName.h>
#include <eirBase/Var.h>
#include <eirBase/VarMap.h>
#include <eirBase/VarPak.h>

class EIREXE_EXPORT CommandLine : public QObject
{
    Q_OBJECT
public:
    typedef VarMap inputOptions;

    class Parser : protected QCommandLineParser
    {
    public:
        Parser();
    };

    class Option : protected QCommandLineOption
    {
    public:
        Option();
    };


public:
    explicit CommandLine(QObject *parent = nullptr);
    void loadFromFile(const QFileInfo qfi);
    void loadFromUrl(const QUrl url);

    static void add(const QCommandLineOption &option);
    static void add(const QJsonObject &jsonObject);
    static void add(const Var::List &VarItem);
    static void add(const QChar &shortName,
             const BasicName::List &longNames,
             const QString & description,
             const QString & valueName=QString(),
             const QString & defaultValue=QString());
    static void multiAdd(QList<QCommandLineOption> &options);
    static void multiAdd(const QJsonArray &JsonObjectList);
    static void multiAdd(const VarMap &VarItems);
    static void addArg(const BasicName argName,
                       const QString argDesc=QString(),
                       const QString syntax=QString());
    static void multiAddArgs(const QStringList &argNameList);
    static Option addHelp();
    static Option addVersion();

public slots:
//    void setupOptions();
    void preprocess();
    void process();

signals:
    void addedOption(BasicName name,
                     QCommandLineOption option);
    void addedArgument(int index1,
                       BasicName name);
    void orgAppChanged(BasicName orgName,
                       BasicName appName);
    void settingProcessed(MultiName name,
                          QString value);
    void preProcessComplete();
    void processComplete();
    void processError();
    void argumentSet(int index1, BasicName name,
                     QString value);
    void optionSet(BasicName, QString value);
    void allResults(VarPak results);

private:
    BasicName mOrgName;
    BasicName mAppName;
    VarMap mSettings;
};

