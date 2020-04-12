// file: {repo: EIRC2}./src/libs/eirExe/ApplicationHelper.h
#pragma once
#include "eirExe.h"

#include <QObject>

#include <QFile>
#include <QTemporaryDir>

#include <eirBase/Var.h>
class CommandLine;
class ErrorHandler;
class Settings;

class EIREXE_EXPORT ApplicationHelper : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationHelper(QObject *parent = nullptr);
//    ~ApplicationHelper();
    QFile * tempFile(const QString &ext,
                     QObject * parent=nullptr);

public slots:
    void run();

protected:

protected slots:
    void initCommandLine();
//    virtual void setupCommandLine() {;}
  //  virtual void processCommandLine() {;}
    void initSettings();

public: // static

signals:
    void initFinished();

private:
    QTemporaryDir * mpTempDir=nullptr;
    Settings * mpSettings=nullptr;
    CommandLine * mpCommandLine=nullptr;
    QList<QFile *> mTempFiles;
};

