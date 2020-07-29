#pragma once
#include "eirRectFind.h"

#include <QObject>

#include <eirType/BasicName.h>
#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>

class EIRRECTFIND_EXPORT RectFinder : public QObject
{
    Q_OBJECT
public:
    explicit RectFinder(QObject *parent = nullptr);
    RectFinder(ConfigObject *cfgObj,
               QObject *parent = nullptr);
    void set(ConfigObject *cfgObj);
    bool contains(const BasicName &name) const;
    cvCascade *cascade(const BasicName &name) const;

public slots:
    void load(const BasicName &name,
              const QFileInfo &xmlFile);
    void configure(const BasicName &name,
                   const Configuration &configSegment);

signals:

private:
    ConfigObject * mpConfogObject;
    QMap<BasicName, cvCascade *> mNameCascadeMap;

};

