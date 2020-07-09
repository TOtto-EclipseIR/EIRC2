#include "RectFinder.h"

#include <QDir>
#include <QImage>
#include <QPainter>

#include <eirBase/Debug.h>
#include <eirBase/Success.h>

#include "ImageMarker.h"

RectFinder::RectFinder(ConfigObject * configObject,
                       const RectFinderClass &finderClass)
    : mpConfig(configObject)
    , cmFinderClass(finderClass)
    , mParameters(cmFinderClass)
    , cmpCascade(new RectCascade())
{
    TRACEQFI << cmFinderClass.name();
    TODO(make QObject(parent));
}

void RectFinder::configure()
{
    TRACEFN;
    mResourceConfig.setName("RectFinder:ResourceConfig");
    mClassConfig.setName("RectFinder:ClassConfig");
    mResourceConfig = config()->configuration().extract("/Detect/Resources");
    mClassConfig = config()->configuration().extract("/Detect/Resources/HaarCascade/"+cmFinderClass.name());
    mResourceConfig.dump();
    mClassConfig.dump();
}

QFileInfo RectFinder::cascadeFileInfo() const
{
    return cmpCascade->fileInfo();
}

ConfigObject *RectFinder::config()
{
    return mpConfig;
}

QSize RectFinder::coreSize() const
{
    TSTALLOC(cmpCascade);
    return cmpCascade->coreSize();
}

void RectFinder::clearImage()
{
    mInputMat = cvMat();
    mInputImage = QImage();
    mDetectImage = QImage();
    mRectImage = QImage();
}

bool RectFinder::isReadyImage() const
{
    TRACEFN;
    Success success;
    EXPECT(cmpCascade);
    success.ok(cmpCascade);
    EXPECTNOT(cmpCascade->isEmpty());
    if (success.ok()) success.ok( ! cmpCascade->isEmpty());
    NEEDDO(more);
    return success.ok();
}

bool RectFinder::loadResources()
{
    TRACEFN;
    TSTALLOC(cmpCascade);
    QFileInfo cascadeFileInfo(
        QDir(mResourceConfig.value("/BaseDir").currentVari().toString()),
        mClassConfig.value("XmlFile").currentVari().toString());
    TRACE << cascadeFileInfo;
    return cmpCascade->load(cascadeFileInfo);
}
/*
bool RectFinder::loadConfigResources()
{
    TRACEFN; NEEDDO(it); NEEDRTN(Success());
    QFileInfo cascadeFileInfo(
        QDir(mResourceConfig.value("/BaseDir").currentVari().toString()),
        mClassConfig.value("XmlFile").currentVari().toString());
    return false;
}

bool RectFinder::loadFinderResources(const QDomElement &resourceRootElement)
{
    TRACEQFI << resourceRootElement.tagName();
    NEEDDO(QDomElement); NEEDRTN(false);
    return false;
}
*/
bool RectFinder::setInputImage(const QString &inputfileName)
{
    clearImage();
    mInputMat.load(QFileInfo(inputfileName));
    return ! mInputMat.isEmpty();
}

QSize RectFinder::inputSize() const
{
    return QSize(mInputMat.cols(), mInputMat.rows());
}

//int RectFinder::find(RectFinderParameters parms)
int RectFinder::find()
{
    TRACEFN;
    TSTALLOC(cmpCascade);
    BEXPECTNOT(cmpCascade->isEmpty());
    RectFinderParameters parms(RectFinderClass::Face);
    NEEDDO(RectFinderParameters);
    parms.calculate(inputSize());
    cvRectStdVector rectVector =
            cmpCascade->find(mInputMat,
                             parms.scaleFactor(),
                             parms.minNeighbors(),
                             parms.minSize(),
                             parms.maxSize());
    return fillRectList(rectVector);
}

QImage RectFinder::inputImage(const QImage::Format format)
{
    if ( ! mInputImage.isNull())    return mInputImage;

    NEEDDO(it); NEEDUSE(format); NEEDDO(return);

    return QImage();
}

QImage RectFinder::detectImage(const QImage::Format format)
{
    NEEDDO(it); NEEDUSE(format); NEEDDO(return);
    return QImage();
}

QImage RectFinder::rectImage(const QImage::Format format)
{
    TRACEQFI << format;
    if ( ! mRectImage.isNull()) return mRectImage;

    QImage outImage = detectImage().convertToFormat(format);
    mRectImage = ImageMarker::markRetangles(outImage, mRectList);
    return mRectImage;
}

RectList RectFinder::rectList() const
{
    return mRectList;
}

int RectFinder::fillRectList(const cvRectStdVector &cvVector)
{
    WANTDO(Move to rectCascade);
    mRectList.clear();
    foreach (cvRect cvrc, cvVector.toCvRectStdVector())
        mRectList.append(QRect(cvrc));
    return mRectList.size();
}

