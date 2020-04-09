#pragma once
#include "eirExe.h"

#include <QObject>
#include "ApplicationHelper.h"

#include <QCoreApplication>

class QFile;


class EIREXE_EXPORT Console : public ApplicationHelper
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);

public slots:
    void writeLine(const QString &qs);
    void writeErr(const QString &qs);

signals:

private:
    QCoreApplication * mpCoreApp=nullptr;
    QFile * mpIn=nullptr;
    QFile * mpOut=nullptr;
    QFile * mpErr=nullptr;
};

