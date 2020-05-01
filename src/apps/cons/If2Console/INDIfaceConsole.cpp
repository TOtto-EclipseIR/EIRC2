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
    CONNECT(this, &INDIfaceConsole::imageProcessed,
            this, &INDIfaceConsole::nextImage);
    CONNECT(this, &INDIfaceConsole::processingComplete,
            this, &QCoreApplication::quit);
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
    QImage greyImage = inImage
            .convertToFormat(QImage::Format_Grayscale8);
    EXPECT(inImage.save(QFileInfo(mCapture2Dir,
                             inFileInfo.fileName()).filePath()));
    EXPECT(greyImage.save(QFileInfo(mGreyInputDir,
                             inFileInfo.fileName()).filePath()));
    TSTALLOC(mpFFDetector);
    mpFFDetector->setGreyImage(greyImage, inFileInfo);
    mpFFDetector->findRectangles();
    mRectList = mpFFDetector->rectangles();
    QImage rectangleImage
            = mpFFDetector->markRectangles(false,
                                mMarkedRectangleDir);
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
    cfg.insert("Output/Capture2Dir", "Capture2");
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
    mCapture2Dir = outputDir(mBaseDir, config.value("Output/Capture2").toString());
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
        emit imageProcessed(qfi);
    }
}

