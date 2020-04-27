#include "INDIfaceConsole.h"

#include <QDateTime>
#include <QDir>
#include <QImage>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/CommandLine.h>
#include <eirExe/Settings.h>
#include <eirQtCV4/Detector.h>


INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
{
    TRACEFN
    setObjectName("INDIfaceConsole");
    CONNECT(this, &INDIfaceConsole::applicationInitd,
            this, &INDIfaceConsole::initializeResources);
    CONNECT(this, &INDIfaceConsole::resoursesInitd,
            this, &INDIfaceConsole::processCommandLine);
    CONNECT(this, &INDIfaceConsole::pendingFilesSet,
            this, &INDIfaceConsole::scanInputDir);
    CONNECT(this, &INDIfaceConsole::inputScanned,
            this, &INDIfaceConsole::nextImage);
    TRACERTV()
}

void INDIfaceConsole::configure(const VarPak &config)
{
    TRACEQFI << config.id().name()();
    mConfiguration = config;
}

QString INDIfaceConsole::configString(const MultiName &key) const
{
    return mConfiguration.value(key).toString();
}

QDir INDIfaceConsole::outputDir(QDir baseDir,
                                QString dirName)
{
    TRACEQFI << baseDir.absolutePath() << dirName;
    dirName.replace('@', QDateTime::currentDateTime().toString("DyyyyMMdd-Thhmm"));
    QDir outDir = baseDir;
    EXPECT(outDir.mkpath(dirName));
    EXPECT(outDir.cd(dirName));
    EXPECT(outDir.exists());
    return outDir;
}

void INDIfaceConsole::processInputImage(const QFileInfo &inFileInfo)
{
    TRACEQFI << inFileInfo;
    QImage inImage = QImage(inFileInfo.filePath());
    QImage greyImage = toGrey(inImage);
    greyImage.save(QFileInfo(mGreyInputDir,
                             inFileInfo.fileName()).filePath());
    TSTALLOC(mpFFDetector);
    mpFFDetector->setGreyImage(greyImage);
    mpFFDetector->findRectangles();
    mRectList = mpFFDetector->rectangles();
    QImage rectangleImage
            = mpFFDetector->markRectangles(false,
                                mMarkedRectangleDir);
    emit imageProcessed(inFileInfo);
}

QImage INDIfaceConsole::toGrey(const QImage &inputImage)
{
    TRACEQFI << inputImage;
    WANTDO("move to pixel library")
    if (inputImage.isGrayscale())
        return inputImage;
    QImage outputImage(inputImage.size(),
                       QImage::Format_Grayscale8);
    QImage rgbImage = inputImage;
    if ( ! rgbImage.format() == QImage::Format_RGB32)
        rgbImage.toPixelFormat(QImage::Format_RGB32);
    for (int r = 0; r < rgbImage.height(); ++r)
        for (int c = 0; c < rgbImage.width(); ++c)
            outputImage.setPixel(c, r,
                qGray(rgbImage.pixel(c, r)));
    return outputImage;
}

void INDIfaceConsole::findFFRectangles(const Region region)
{
    TRACEQFI << region;
    mpFFDetector->findRectangles(region);
}

CommandLine *INDIfaceConsole::commandLine()
{
    TRACEQFI << (Console::commandLine()
                ? Console::commandLine()->objectName()
                : "{null}");
    return Console::commandLine();
}

void INDIfaceConsole::initializeApplication()
{
    TRACEFN
    mpObjdetect = new QtCVobjdetect(this);
    TSTALLOC(mpObjdetect);
    emit applicationInitd();
}

void INDIfaceConsole::initializeResources()
{
    TRACEFN
    TSTALLOC(mpObjdetect);

    VarPak cfg(Id("QuickConfig"));
    cfg.insert("Output/BaseDir", "./Output/@");
    cfg.insert("Output/GreyInputDir", "GreyInput");
    cfg.insert("Output/MarkedDetectDir", "MarkedDetect");
    cfg.insert("Detect/Face/RectanglesDir", "DetectFace/Rectangles");
    cfg.insert("Detect/Face/HeatMapDir", "DetectFace/HeatMap");
    setOutputDirs(cfg);

    mpFFDetector = mpObjdetect->newDetector(ObjectType::FrontalFace);
    TSTALLOC(mpFFDetector);
    mpFFDetector->initialize(QFileInfo(QDir("../detectors"),
                                       "DefaultFrontalFace.xml"),
                             cfg);
    WANTDO("LEDetector")
    WANTDO("REDetector")
    emit resoursesInitd();
}

void INDIfaceConsole::processCommandLine()
{
    TRACEFN
    TSTALLOC(commandLine());
    TODO(setup Options & pos Args)
    commandLine()->process();
    QFileInfoList files = commandLine()->fileArgumentInfoList();
    mPendingFiles = files;
    TRACE << "emit pendingFilesSet()" << files;
    emit pendingFilesSet();
}

void INDIfaceConsole::setOutputDirs(const VarPak &config)
{
    mBaseDir = outputDir(QDir(), config.value("Output/BaseDir").toString());
    mGreyInputDir = outputDir(mBaseDir, config.value("Output/GreyInputDir").toString());
    mMarkedRectangleDir = outputDir(mBaseDir,
                                    config.value("Detect/Face/RectanglesDir").toString());
    mHeatmapDir = outputDir(mBaseDir, config.value("Detect/Face/HeatMapDir").toString());
}

void INDIfaceConsole::scanInputDir()
{
    TRACEQFI << "mPendingFiles.size()=" << mPendingFiles.size();
    if (mPendingFiles.isEmpty())
    {
        emit inputDirEmpty();
    }
    else
    {
        emit inputScanned();
    }
}

void INDIfaceConsole::nextImage()
{
    TRACEFN
    if (mPendingFiles.isEmpty())
    {
        emit processingComplete();
    }
    else
    {
        QFileInfo qfi = mPendingFiles.takeFirst();
        TRACE << qfi;
        processInputImage(qfi);
    }
}

#if false
void INDIfaceConsole::startWork()
{
    TRACEFN
    setBaseDir("D:/INDIface/INDIout/Console/@");
    mInputDir.setPath("D:/INDIface/INDIin/Console");
    QFileInfoList files = mInputDir.entryInfoList(QDir::Files);
    foreach (QFileInfo qfi, files)
    {
        TRACE << qfi;
        if (qfi.suffix().startsWith("jp", Qt::CaseInsensitive))
            mPendingFiles << qfi;
    }
    QTimer::singleShot(100, this, &INDIfaceConsole::nextImage);
}

int INDIfaceConsole::calculateScale(const QSize sz)
{
    TRACEQFI << sz;
    int dim = qMax(sz.width(), sz.height());
    int scale = 1 + (dim / 2048);
    TRACE << scale << dim;
    return qMax(1, scale);

}

QDir INDIfaceConsole::setBaseDir(QString basePath)
{
    TRACEQFI << basePath;
    basePath.replace("@", QDateTime::currentDateTime()
                     .toString("DyyyyMMddThhmm"));
    QDir baseDir(basePath);
    if ( ! baseDir.exists()) baseDir.mkpath(".");
    return mBaseDir = baseDir;
}

QDir INDIfaceConsole::outputDir(const QString &subdirName) const
{
    TRACEQFI << subdirName;
    QDir outDir(mBaseDir);
    outDir.cd(subdirName);
    if ( ! outDir.exists())
        WEXPECT(outDir.mkpath("."));
    return outDir;
}

QImage INDIfaceConsole::processInputImage(const QImage &inImage) const
{
    TRACEQFI << inImage;
    QImage outImage(inImage.size() / scale, QImage::Format_Indexed8);
    TRACE << outImage << outImage.sizeInBytes();
    QVector<QRgb> greyColorTable(256);
    for (unsigned char b = 0; b < 255; ++b)
        greyColorTable[b] = qRgb(b,b,b);
    outImage.setColorTable(greyColorTable);

    for (int row = 0; row < inImage.size().height()/scale; ++row)
        for (int col = 0; col < inImage.size().width()/scale; ++col)
            outImage.setPixel(col, row,
                qGray(inImage.pixel(col*scale, row*scale)));

    return outImage;
}

void INDIfaceConsole::findRectangles(const QFileInfo qfi,
                                const QImage &inImage)
{
    TRACEQFI << qfi << inImage;
#ifdef STUB_OPENCV4
    MUSTDO(setImage) MUSTDO(findRectamgles)
#else
    MUSTDO(setImage) MUSTDO(findRectamgles)
#endif
}

void INDIfaceConsole::initApplication()
{
    TRACEFN
    writeLine("Welcome to INDIfaceConsole");
    CONNECT(this, &ApplicationHelper::initFinished,
            this, &INDIfaceConsole::initialize);
    CONNECT(this, &INDIfaceConsole::applicationInitd,
            this, &INDIfaceConsole::initialize);
    CONNECT(this, &INDIfaceConsole::resoursesInitd,
            this, &INDIfaceConsole::process);
            qApp, &QCoreApplication::quit);
    QTimer::singleShot(100, this, &ApplicationHelper::run);
}

void INDIfaceConsole::initialize()
{
    TRACEFN
            writeLine("Initializing Frontal Face Detector");
#ifdef STUB_OPENCV4
    WANTDO("initialize detector")
#else
    WANTDO("initialize detector")
#endif
    emit resoursesInitd();
}

void INDIfaceConsole::process()
{
    TRACEFN
    startWork();
}

void INDIfaceConsole::nextImage()
{
    TRACEQFI << mPendingFiles.size();

    if (mPendingFiles.isEmpty())
    {
        emit processed();
    }
    else
    {
        QFileInfo qfi = mPendingFiles.takeFirst();
        QDir outDir = outputDir("GreyInput");
        QImage imageIn = QImage(qfi.filePath());
        int downScale = calculateScale(imageIn.size());
        QImage imageGreyIn = processInputImage(imageIn, downScale);
        QFileInfo outFI = outDir.filePath(qfi.fileName());
        TRACE << outFI.filePath();
        WEXPECT(imageGreyIn.save(outFI.filePath()));
/*      findRectangles(qfi, imageIn);
        MUSTDO(drawRectangles)
*/      QTimer::singleShot(100, this, &INDIfaceConsole::nextImage);
    }
}
#endif // 0
