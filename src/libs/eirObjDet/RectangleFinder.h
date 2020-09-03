#pragma once

#include <QObject>

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QUuid>
#include <QDir>

#include <eirQtCV/cvCascade.h>

#include "CascadeType.h"

class RectangleFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectangleFinder(QObject *parent = nullptr);
    bool isLoaded(const CascadeType type);

public slots:
    void setCascadeBaseDir(const QString &cascadeBaseDirName);
    void loadCascade(const CascadeType type,
                     const QString &cascadeXmlFileName);

signals:
    void cascadeBaseDirSet(CascadeType type,
                           QDir cascadeBaseDir);
    void cascadeLoaded(CascadeType type,
                       QFileInfo cascadeXmlFileInfo);

};

