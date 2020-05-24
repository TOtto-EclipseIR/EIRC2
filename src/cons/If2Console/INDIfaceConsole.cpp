// file: {repo: EIRC2}./src/cons/INDIfaceConsole.cpp
#include "INDIfaceConsole.h"

#include <QDateTime>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirType/QQFileInfo.h>
#include <eirExe/CommandLine.h>
#include <eirExe/CommandLineClientInterface.h>
#include <eirExe/ConfigObject.h>
#include <eirExe/FileInfoQueue.h>
#include <eirExe/LegacySettings.h>

#include "If2CommandLine.h"

#ifdef EIRC2_IF2CONSOLE_TAKETWO23
INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
    , mpConfig(new ConfigObject(parent))
//    , mpFileInfoQueue(new FileInfoQueue(parent))
{
    TRACEFN
    setObjectName("INDIfaceConsole");
//    TSTALLOC(mpFileInfoQueue)
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeApplication);
    TRACERTV()
}

void INDIfaceConsole::initializeApplication()
{
    TRACEFN
    writeLine(">>>Hello INDI Console from initializeApplication() at "
                       + QDateTime::currentDateTime().toString());
    writeLine(QString("   %1 %2 from %3")
              .arg(core()->applicationName())
              .arg(core()->applicationVersion())
              .arg(core()->organizationName()));
    writeLine("===Raw Executable Arguments:");
    foreach (QString arg, commandLine()->exeArguments())
        writeLine("---{" + arg + "}");
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::setupCommandLine);
}


void INDIfaceConsole::setupCommandLine()
{
    TRACEFN
    If2CommandLine interface;
    rCommandLine().set(&interface);
    rCommandLine().process();
    rCommandLine().set(nullptr);
    rCommandLine().expandDirectories();
    EMIT(commandLineSetup());
    QTimer::singleShot(100, this, &INDIfaceConsole::setConfiguration);
}

void INDIfaceConsole::setConfiguration()
{
    TRACEFN
    mpConfig->set(commandLine()->configuration());
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeResources);

}

void INDIfaceConsole::initializeResources()
{
    TRACEFN
    NEEDDO("rectFinder::initialize() x 3~5")
    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::startProcessing);
}

void INDIfaceConsole::startProcessing()
{
    TRACEFN
    mImageFileQueue = commandLine()->positionalFileInfoList();
    TODO(?)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::nextFile()
{
    TRACEFN
    while ( ! mImageFileQueue.isEmpty())
    {
        QQFileInfo fileInfo = mImageFileQueue.takeFirst();
        if (fileInfo.isNull())  continue;
        mCurrentImageFile = fileInfo;
        QTimer::singleShot(100, this, &INDIfaceConsole::processFile);
        return;
    }
    QTimer::singleShot(100, this, &INDIfaceConsole::finishProcessing);
}

void INDIfaceConsole::processFile()
{
    TRACEQFI << "mCurrentImageFile:" << mCurrentImageFile;
    NEEDDO(it)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::finishProcessing()
{
    TRACEFN
    NEEDDO(it)
    QTimer::singleShot(100, core(), &QCoreApplication::quit);
}

#else // TAKEONE
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
    QImage colorizedImage = greyImage
            .convertToFormat(QImage::Format_ARGB32);
    EXPECT(inImage.save(QFileInfo(mCapture2Dir,
                             inFileInfo.fileName()).filePath()));
    EXPECT(greyImage.save(QFileInfo(mGreyInputDir,
                             inFileInfo.fileName()).filePath()));
#if 0
    TSTALLOC(mpFFDetector);
    mpFFDetector->setGreyImage(greyImage, inFileInfo);
    mpFFDetector->findRectangles();
    mRectList = mpFFDetector->rectangles();
    HaarRectangles hRect;
    hRect << mRectList;
    hRect.group();
    QList<HaarRectangles::HaarRectangleResult> groupedCandidates
            = hRect.groupedCandidates();
    QImage rectangleImage
            = mpFFDetector->markRectangles(colorizedImage,
                                mMarkedRectangleDir);
    hRect.markCandidates(colorizedImage, inFileInfo,
                                mMarkedCandidateDir);
    QImage candidateImage = hRect.markAllCandidates(inImage, inFileInfo,
                                mMarkedDetectDir);
#endif
#if 0
    foreach (HaarRectangles::HaarRectangleResult hrr, groupedCandidates)
    {
        QQRect candidateRect = hrr.candidate;
        QQRect overCrop = candidateRect * 1.25;
        QString baseFileName = inFileInfo.completeBaseName();
        QString outputFileName = QString("%1+%2.%3").arg(baseFileName)
                .arg(hrr.rank, 2, 10, QChar('0')).arg("JPG");
        WANTDO("Convert grey back to color for Rgb writing; save PNG")
        QImage markedFace = candidateImage.copy(overCrop);
        QImage detectFace = inImage.copy(overCrop);
        WEXPECT(detectFace.save(mFaceDetectDir.filePath(outputFileName)))
        WEXPECT(markedFace.save(mMarkedFaceDir.filePath(outputFileName)))
    }
#endif
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
    if (QImage::Format_RGB32 != rgbImage.format())
        rgbImage.toPixelFormat(QImage::Format_RGB32);
    for (int r = 0; r < rgbImage.height(); ++r)
        for (int c = 0; c < rgbImage.width(); ++c)
            outputImage.setPixel(c, r,
                qGray(rgbImage.pixel(c, r)));
    return outputImage;
}
#if 0
void INDIfaceConsole::findFFRectangles(const Region region)
{
    TRACEQFI << region;
    mpFFDetector->findRectangles(region);
}
#endif


void INDIfaceConsole::setOutputDirs(const VarPak &config)
{
    mBaseDir = outputDir(QDir(),
                    config.value("Output/BaseDir").toString());
    mCapture2Dir = outputDir(mBaseDir,
                    config.value("Output/Capture2Dir").toString());
    mGreyInputDir = outputDir(mBaseDir,
                    config.value("Output/GreyInputDir").toString());
    mMarkedDetectDir = outputDir(mBaseDir,
                    config.value("Output/MarkedDetectDir").toString());
    mMarkedFaceDir = outputDir(mBaseDir,
                    config.value("Output/MarkedFaceDir").toString());
    mFaceDetectDir = outputDir(mBaseDir,
                    config.value("Output/FaceDetectDir").toString());
    mMarkedRectangleDir = outputDir(mBaseDir,
                    config.value("Output/MarkedRectangleDir").toString());
    mHeatmapDir = outputDir(mBaseDir,
                    config.value("Output/HeatMapDir").toString());
    mMarkedCandidateDir = outputDir(mBaseDir,
                    config.value("Output/MarkedCandidateDir").toString());
}

void INDIfaceConsole::scanInputDir()
{
    if (mpFileInfoQueue->isPendingEmpty())
    {
        mpFileInfoQueue->processIncoming();
    }
    else
    {
        emit inputScanned();
    }
}

void INDIfaceConsole::nextImage()
{
    TRACEQFI << mpFileInfoQueue->pendingCount();
    if (mpFileInfoQueue->isPendingEmpty())
    {
        emit processingComplete();
        QTimer::singleShot(100, qApp, &QCoreApplication::quit);
    }
    else
    {
        QFileInfo qfi = mpFileInfoQueue->takeFirstPending();
        TRACE << qfi;
        processInputImage(qfi);
        QTimer::singleShot(100, this, &INDIfaceConsole::nextImage);
    }
}

#endif
