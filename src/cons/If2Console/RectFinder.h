#pragma once

#include <QDomElement>
#include <QImage>
#include <QList>
#include <QPen>
#include <QRect>

#include <eirExe/ConfigObject.h>

#include "cvMat.h"
#include "cvRect.h"
#include "cvRectStdVector.h"
#include "RectCascade.h"
#include "RectFinderClass.h"
#include "RectFinderParameters.h"

typedef QList<QRect> RectList;

class RectFinder
{
public:
    RectFinder(ConfigObject * configObject,
               const RectFinderClass &finderClass);
    void configure();

    // Interface
    QFileInfo cascadeFileInfo() const;
    ConfigObject *config();
    QSize coreSize() const;
    void clearImage();
    void clearResults();
    bool isReadyImage() const;

    // Detector Resources
    bool loadResources();
    /*
    bool loadConfigResources();
    bool loadFinderResources(const MultiName::List &resourceNameList);
    bool loadFinderResources(const MultiName &resourceName);
    bool loadFinderResourcesXml(const QFileInfo &resourceFile);
    bool loadFinderResourcesXml(const QFileInfoList &resourceFileList);
    bool loadFinderResources(const QDomElement &resourceRootElement);
    bool loadFinderResources(const QList<QDomElement> &resourceRootElementList);
    */

    // Detector Processing
    bool setInputImage(const QString &inputfileName);
    QSize inputSize() const;
    int find();

    // Detector Results
    QImage inputImage(const QImage::Format format=QImage::Format_ARGB32);
    QImage detectImage(const QImage::Format format=QImage::Format_Grayscale8);
    QImage rectImage(const QImage::Format format=QImage::Format_ARGB32);
    cvRect::Vector cvRectVector() const;
    RectList rectList() const;

protected:
    int fillRectList(const cvRectStdVector & cvVector);

private:
    ConfigObject * mpConfig=nullptr;
    const RectFinderClass cmFinderClass;
    RectFinderParameters mParameters;
    RectCascade * cmpCascade=nullptr;
    Configuration mResourceConfig;
    Configuration mClassConfig;
    cvMat mInputMat;
    QImage mInputImage;
    QImage mDetectImage;
    QImage mRectImage;
    RectList mRectList;
};

