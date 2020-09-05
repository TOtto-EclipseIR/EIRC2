#include "cvCascade.h"

#include <QColor>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
{
    TRACEQFI << type;
}

cvCascade::Type cvCascade::type() const
{
    return cmType;
}

BasicName cvCascade::typeName() const
{
    return typeName(cmType);
}

bool cvCascade::isNull() const
{
    return nullType == cmType;
}

bool cvCascade::loadCascade(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cmType << cascadeXmlInfo;
    unload();
    cv::CascadeClassifier * pcvcc = new cv::CascadeClassifier;
    if (pcvcc->load(cvString(cascadeXmlInfo.absoluteFilePath())))
    {
        mpClassifier = pcvcc;
        mCascadeXmlInfo = cascadeXmlInfo;
    }
    EXPECTNOT(mpClassifier->empty());
    return nullptr != mpClassifier;
}

bool cvCascade::loadCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cmType << cascadeXmlInfo;
    mCoreSize = QSize();
    XmlFile xmlFile(cascadeXmlInfo.absoluteFilePath());
    bool loaded = xmlFile.load();
    EXPECT(loaded);
    if ( ! loaded) return loaded;
    QDomElement rootDE = xmlFile.rootElement();
    DUMPVAL(rootDE.tagName());
    QDomElement topDE = rootDE.firstChildElement();
    DUMPVAL(topDE.tagName());
    DUMPVAL(topDE.attribute("type_id"));
    QDomElement heightDE = topDE.firstChildElement("height");
    QDomElement widthDE  = topDE.firstChildElement("width");
    QString sHeight = heightDE.text();
    QString sWidth  = widthDE.text();
    int height = sHeight.toInt(), width = sWidth.toInt();
    QSize sz(width, height);
    DUMP << width << height << sz;
    if (sz.isValid()) mCoreSize = sz;
    return mCoreSize.isValid();
}

bool cvCascade::notLoaded() const
{
    return mpClassifier ? mpClassifier->empty() : true;
}

bool cvCascade::isLoaded() const
{
    return mpClassifier ? (! mpClassifier->empty()) : false;
}

void cvCascade::unload()
{
    if (mpClassifier)
    {
        delete mpClassifier;
        mpClassifier = nullptr;
    }
    mCascadeXmlInfo = QFileInfo();
    mCoreSize = QSize();
}

QSize cvCascade::coreSize() const
{
    TRACEQFI << mCoreSize;
    return mCoreSize;
}

QFileInfo cvCascade::cascadeFileInfo() const
{
    return mCascadeXmlInfo;
}

cv::CascadeClassifier *cvCascade::classifier()
{
    return mpClassifier;
}

int cvCascade::detectRectangles(const Configuration &rectFinderConfig,
                                const QQImage &inputImage,
                                const bool showDetect,
                                const QQRect &region)
{
    TRACEQFI << inputImage << region;
    rectFinderConfig.dump();

    EXPECTNOT(inputImage.isNull());
    if  (inputImage.isNull()) return -1; // null image      /* /========\ */
    mMethodString.clear();
    mDetectMat.clear();
    mRectList.clear();

    mDetectMat.setGrey(inputImage);
    DUMP << mDetectMat.dumpString();
    if (showDetect)
    {
        cv::imshow("DetectMat", mDetectMat.mat());
        cv::waitKey(5000);
    }

    Parameters parms(rectFinderConfig);
    parms.calculate(cmType, mDetectMat.size(), coreSize());
#if 0
    QSize minSize = parms.minSize();
    QSize maxSize = parms.maxSize();
#else
    NEEDDO(RemoveForFlight);
    QSize minSize(80,80);
    QSize maxSize(160,160);
#endif
    mMethodString = parms.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;
    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        parms.factor(),
                        parms.neighbors(),
                        parms.flags(),
                        cv::Size(minSize.width(), minSize.height()),
                        cv::Size(maxSize.width(), maxSize.height()));

    foreach (cv::Rect cvrc, cvRectVector)
        mRectList << QQRect(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
    return mRectList.size();
}

cvMat cvCascade::detectMat() const
{
    return mDetectMat;
}

QQImage cvCascade::detectImage() const
{
    MUSTDO(toImage);
    return QQImage();
    //return mDetectMat.toImage();

}

QQRectList cvCascade::rectList() const
{
    return mRectList;
}

QString cvCascade::methodString() const
{
    return mMethodString;
}

BasicName cvCascade::typeName(cvCascade::Type type)
{
    switch (type)
    {
        case nullType:      return "{null}";
        case PreScan:       return "PreScan";
        default:
            MUSTDO(handle);
            break;
    }
    return "{unknown}";
}


#if 0
cvCascade::cvCascade(const CascadeType &cascadeType)
    : cmCascadeType(cascadeType)
{
    TRACEQFI << cascadeType.name();
}

void cvCascade::configure(const Configuration &config)
{
    TRACEFN;
    config.dump();
    mCascadeConfig = config;
    //mParameters.configureCascade(config);
}

CascadeType cvCascade::cascadeType() const
{
    return cmCascadeType;
}
bool cvCascade::imreadInputMat(const QQFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    mInputMat.imread(inputFileInfo.absoluteFilePath(), cv::IMREAD_COLOR);
    TRACE << mInputMat.dumpString();
    EXPECT(mInputMat.isValid());
    return mInputMat.isValid();
}

cvCascade::RectList cvCascade::detect()
{
    TRACEQFI << mInputMat.dumpString();
    TODO(inputSize&coreSize);
    CascadeParameters parms(mCascadeConfig);
    parms.calculate(mInputMat.toSize(), QSize(32,32));
    QSize minSize = parms.minSize();
    QSize maxSize = parms.maxSize();
    cvMat detectMat(mInputMat.rows(), mInputMat.cols(), CV_8UC1);
    mInputMat.makeGrey(detectMat.mat());
    mDetectMat.set(detectMat.mat());
    std::vector<cv::Rect> cvRectVector;
    cvCascade::RectList results;
    makeMethodString(parms);
    TRACE << methodString();



    foreach (cv::Rect cvrc, cvRectVector)
    {
        QRect qrc(cvrc.x, cvrc.y, cvrc.width, cvrc.height);
        results << qrc;
    }

    TRACE << results.size() << "Rectangles";
    mRectList = results;
    return results;
}

QString cvCascade::methodString() const
{
    return mMethodString;
}

bool cvCascade::imwriteMarkedImage(QQFileInfo markFileInfo)
{
    TRACEQFI << markFileInfo;
    cvMat markMat(mInputMat.cols(), mInputMat.rows(), mInputMat.type());
    mInputMat.mat().copyTo(markMat.mat());
    markMat.markRectangles(mRectList);

    return markMat.imwrite(markFileInfo.absoluteFilePath());
}

bool cvCascade::getCoreSize(const QFileInfo &cascadeXmlInfo)
{
    TRACEQFI << cascadeXmlInfo;
    mCoreSize = QSize(32, 32);
    NEEDDO(it);
    return false;
}

void cvCascade::makeMethodString(const CascadeParameters &parms)
{
    TRACEFN;
    parms.dumpList();
    mMethodString = QString("Factor=%1,Neighbors=%2"
                            ",MinSize=%3x%4,MaxSize=%5x%6,%7")
            .arg(parms.factor()).arg(parms.neighbors())
            .arg(parms.minSize().width()).arg(parms.minSize().height())
            .arg(parms.maxSize().width()).arg(parms.maxSize().height())
            .arg(mCascadeXmlInfo.completeBaseName());

}
#endif

cvCascade::Parameters::Parameters(const Configuration &cascadeConfig)
{
    TRACEFN;
    cascadeConfig.dump();
    mConfig = cascadeConfig;
}

void cvCascade::Parameters::calculate(const cvCascade::Type type,
                                      const QQSize imageSize,
                                      const QQSize coreSize)
{
    TRACEQFI << cvCascade::typeName(type)() << imageSize << coreSize;
    NEEDUSE(type);
    NEEDUSE(imageSize);
    NEEDUSE(coreSize);

    double fac = parseFactor();
    mFactor = qIsNull(fac) ? 1.160 : fac;
    NEEDDO("Default Based on Image/Core size & MaxDetectors, etc.");

    int neigh = mConfig.signedInt("Neighbors");
    mNeighbors = (neigh >= 0) ? neigh : 2;

    DUMP << dumpList();
}

double cvCascade::Parameters::factor() const
{
    return mFactor;
}

int cvCascade::Parameters::neighbors() const
{
    return mNeighbors;
}

int cvCascade::Parameters::flags() const
{
    return mFlags;
}

QSize cvCascade::Parameters::minSize() const
{
    return mMinSize.isValid() ? mMinSize : QSize(0,0);
}

QSize cvCascade::Parameters::maxSize() const
{
    return mMaxSize.isValid() ? mMaxSize : QSize(0,0);
}

QString cvCascade::Parameters::methodString(const QFileInfo &cascadeXmlInfo) const
{
    return QString("Factor=%1,Neighbors=%2,MinSize=%3x%4,MaxSize=%5x%6,%7")
            .arg(factor()).arg(neighbors())
            .arg(minSize().width()).arg(minSize().height())
            .arg(maxSize().width()).arg(maxSize().height())
            .arg(cascadeXmlInfo.completeBaseName());
}

double cvCascade::Parameters::parseFactor()
{
    double result=qQNaN();
    double f = mConfig.real("Factor");
    if (f < 2.000)
        result = 0.0;
    else
        result = 1.000 + f / 1000.0;
    TRACE << f << result;
    EXPECTNE(result, qQNaN());
    return result;
}

QStringList cvCascade::Parameters::dumpList() const
{
    QStringList qsl;
    qsl << QString("%1 = %2").arg("factor").arg(factor());
    qsl << QString("%1 = %2").arg("neighbors").arg(neighbors());
    qsl << QString("%1 = %2").arg("flags").arg(flags());
    qsl << QString("%1 = %2x%3").arg("minSize").arg(minSize().width())
                                               .arg(minSize().height());
    qsl << QString("%1 = %2x%3").arg("maxSize").arg(maxSize().width())
                                               .arg(maxSize().height());
    return qsl;
}

