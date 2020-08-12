#pragma once
#include "eirFinder.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>

class EIRFINDER_EXPORT RectFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectFinder(QObject *parent = nullptr);
    RectFinder(ConfigObject *cfgObj,
               QObject *parent = nullptr);
    void set(ConfigObject *cfgObj);
    void set(const QDir &baseDir);
    bool loaded(const BasicName &cascadeType) const;
    QFileInfo cascadeFileInfo(const BasicName &cascadeType) const;
    cvCascade *cascade(const BasicName &cascadeType) const;

public slots:
    void load(const BasicName &cascadeType,
              const QString &xmlFileName);
    void configure(const Configuration &configSegment);
    void configure(const BasicName &name,
                   const Configuration &configSegment);

signals:

private:
    ConfigObject * mpConfigObject;
    QDir mBaseDir;
    QMap<BasicName, cvCascade *> mNameCascadeMap;
    QMap<BasicName, Configuration> mNameConfigMap;
};

