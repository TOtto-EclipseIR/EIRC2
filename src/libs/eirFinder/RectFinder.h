#pragma once
#include "eirFinder.h"

#include <QObject>

#include <QDir>
#include <QFileInfo>

#include <eirType/BasicName.h>
#include <eirType/EnumerationArray.h>
#include <eirType/QQRectList.h>
#include <eirExe/ConfigObject.h>
#include <eirQtCV/cvCascade.h>
#include <eirQtCV/CascadeType.h>

#include "FinderCascade.h"

class EIRFINDER_EXPORT RectFinder : public QObject
{
    Q_OBJECT
public:
    RectFinder(ConfigObject *cfgObj,
               QObject *parent = nullptr);
    void set(ConfigObject *cfgObj);
    void set(const QDir &baseCascadeDir);
    bool loaded(const CascadeType &cascadeType) const;
    QFileInfo cascadeFileInfo(const CascadeType &cascadeType) const;
    cvCascade cascade(const CascadeType &cascadeType) const;
    QImage findRectImage(const CascadeType &cascadeType) const;
    QStringList methodList(const CascadeType &cascadeType) const;
    QQRectList rectangleList(const CascadeType &cascadeType);
    QImage makeRectImage(const CascadeType &cascadeType,
                         bool all=false);

public slots:
    void load(const CascadeType &cascadeType,
              const QFileInfo &xmlFileInfo);
    void configure(const Configuration &baseConfig);
    void configure(const CascadeType cascadeType,
                   const Configuration &cascadeConfig);
    void set(const CascadeType &cascadeType,
             const QImage &image);
    void findRectangles(const CascadeType &cascadeType);

signals:
    void cascadeLoaded(CascadeType cascadeType);
    void cascadeLoadFailed(CascadeType cascadeType);
    void baseConfigured(Configuration baseConfig);
    void cascadeConfigured(CascadeType cascadeType,
                           Configuration cascadeConfig);
    void imageLoaded(CascadeType cascadeType);
    void imageLoadFailed(CascadeType cascadeType,
                         QString errorString);
    void rectanglesFound(CascadeType cascadeType,
                         int rectangleCount);
    void rectFindFailed(CascadeType cascadeType,
                        QString errorString);

private:
    ConfigObject * mpConfigObject;
    Configuration mBaseConfiguration;
    QDir mBaseCascadeDir;
    QList<FinderCascade> mFinderCascadeList;
//    EnumerationArray<CascadeType, FinderCascade> mFinderCascades;
};

