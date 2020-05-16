// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QFile>
#include <QTemporaryDir>

#include <eirBase/Var.h>
//#include "../EIRC2/src/libs/eirBase/Var.h"
class BaseCommandLine;
class ErrorHandler;
class Settings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
    QFile * tempFile(const QString &ext,
                     QObject * parent=nullptr);
    BaseCommandLine * commandLine(void);


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

