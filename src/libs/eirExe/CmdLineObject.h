#pragma once

#include <QObject>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <eirBase/MultiName.h>

class CmdLineObject : public QObject
{
    Q_OBJECT
public:
    explicit CmdLineObject(QObject *parent = nullptr);

public slots:
    void addOption(const MultiName & name,
                   const QCommandLineOption & option);

signals:
    void constructed(void);
    void optionSet(MultiName name);

private:
    QCommandLineParser mParser;
    QMap<QString /*sortable*/, QCommandLineOption> mOptionMap;
};

