#include "cvCascade.h"

#include <QColor>
#include <QTextStream>
#include <QDomElement>
#include <QPainter>
#include <QPixmap>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include <eirExe/XmlFile.h>
#include <eirXfr/Debug.h>

#include "cvString.h"

cvCascade::cvCascade(const cvCascade::Type &type)
    : cmType(type)
{
    TRACEQFI << type;
    TODO(cv::redirectError);
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

bool cvCascade::loadCoreSize(const QFileInfo &cascadeXmlInfo,
                             int cascadeVersion)
{
    TRACEQFI << cmType << cascadeXmlInfo << cascadeVersion;
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

    if (cascadeVersion != 2 && cascadeVersion != 4)
    {
        QString typeId = topDE.attribute("type_id");
        if (typeId == "opencv-haar-classifier")
            cascadeVersion = 2;
        else if (typeId == "opencv-cascade-classifier")
            cascadeVersion = 4;
    }

    int height, width;
    switch (cascadeVersion)
    {
    case 2:
    {
        QDomElement sizeDE = topDE.firstChildElement("size");
        QString sizeText = sizeDE.text();
        QTextStream ts(&sizeText);
        ts >> width >> height;
    }
        break;

    case 4:
    {
        QDomElement heightDE = topDE.firstChildElement("height");
        QDomElement widthDE  = topDE.firstChildElement("width");
        height = heightDE.text().toInt();
        width  = widthDE.text().toInt();
    }
        break;

    default:
        return false;
    }

    QSize sz(width, height);
    DUMPVAL(sz);
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

QQFileInfo cvCascade::cascadeFileInfo() const
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

    mParameters.set(rectFinderConfig);
    mParameters.calculate(cmType, mDetectMat.size(), coreSize());
#if 1
    QSize minSize = mParameters.minSize();
    QSize maxSize = mParameters.maxSize();
#else
    NEEDDO(RemoveForFlight);
    QSize minSize(80,80);
    QSize maxSize(160,160);
#endif
    mMethodString = mParameters.methodString(mCascadeXmlInfo);
    DUMPVAL(mMethodString);

    std::vector<cv::Rect> cvRectVector;
    classifier()->detectMultiScale(mDetectMat.mat(),
                        cvRectVector,
                        mParameters.factor(),
                        mParameters.neighbors(),
                        mParameters.flags(),
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

cvCascade::Parameters cvCascade::parameters() const
{
    return mParameters;
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
