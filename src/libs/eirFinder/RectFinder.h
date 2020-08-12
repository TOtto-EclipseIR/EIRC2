#pragma once
#include "eirFinder.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>

#include <eirType/BasicName.h>
#include <eirType/QQRectList.h>
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
    QImage findRectImage(const BasicName &cascadeType) const;
    QStringList methodList() const;
    QQRectList rectangleList(BasicName cascadeType);
    QImage makeRectImage(bool all=false);

public slots:
    void load(BasicName cascadeType,
              QString xmlFileName);
    void configure(Configuration baseConfig);
    void configure(BasicName cascadeType,
                   Configuration cascadeConfig);
    void set(QImage image);
    void findRectangles(BasicName cascadeType);

signals:
    void cascadeLoaded(BasicName cascadeType);
    void cascadeLoadFailed(BasicName cascadeType);
    void baseConfigured(Configuration baseConfig);
    void cascadeConfigured(BasicName cascadeType,
                           Configuration cascadeConfig);
    void imageLoaded(BasicName cascadeType);
    void imageLoadFailed(BasicName cascadeType,
                         QString errorString);
    void rectanglesFound(BasicName cascadeType,
                         int rectangleCount);
    void rectFindFailed(BasicName cascadeType,
                        QString errorString);

private:
    ConfigObject * mpConfigObject;
    QDir mBaseDir;
    Configuration mBaseConfig;
    QMap<BasicName, cvCascade *> mNameCascadeMap;
    QMap<BasicName, Configuration> mNameConfigMap;
    QMap<BasicName, QQRectList> mNameRectListMap;
};

