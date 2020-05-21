#include "INDIfaceConsole.h"

#include <QDateTime>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/BaseCommandLine.h>
#include <eirExe/FileInfoQueue.h>
#include <eirExe/Settings.h>

#include "CommandLine.h"

#ifdef EIRC2_IF2CONSOLE_TAKETWO23
INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
    , mpFileInfoQueue(new FileInfoQueue(parent))
    , mpCommandLine(new CommandLine(parent))
{
    TRACEFN
    setObjectName("INDIfaceConsole");
    TSTALLOC(mpFileInfoQueue)
    TSTALLOC(mpCommandLine)
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeApplication);
    TRACERTV()
}

CommandLine *INDIfaceConsole::commandLine()
{
    TSTALLOC(mpCommandLine);
    return mpCommandLine;
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
        writeLine("---{{" + arg + "}");
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeResources);
}

void INDIfaceConsole::initializeResources()
{
    TRACEFN

    VarPak cfg(Id("QuickConfig"));
    cfg.insert("Output/BaseDir", "/INDIface/INDIout/console/@");
    cfg.insert("Output/Capture2Dir", "Capture2");
    cfg.insert("Output/GreyInputDir", "GreyInput");
    cfg.insert("Output/MarkedDetectDir", "MarkedDetect"); //+
    cfg.insert("Output/MarkedFaceDir", "MarkedFace"); //-unmarked
    cfg.insert("Output/FaceDetectDir", "FaceDetect"); //-marked,Width
    cfg.insert("Output/MarkedRectangleDir", "Rectangles"); //+
    cfg.insert("Output/MarkedCandidateDir", "Candidates"); //-Colors
    cfg.insert("Output/HeatMapDir", "HeatMap"); //x
//    setOutputDirs(cfg);

     emit resoursesInitd();
    QTimer::singleShot(100, this, &INDIfaceConsole::processCommandLine);
}

void INDIfaceConsole::processCommandLine()
{
    TRACEFN
#if 0
    TSTALLOC(commandLine());
    commandLine()->addHelpOption();
    commandLine()->addVersionOption();
    commandLine()->addPositionalArgument(MultiName("FilesAndDirs"));

    commandLine()->process();

//    mPendingFileDirs = commandLine()->positionalFileInfoList();
#endif
    mpFileInfoQueue->append(QFileInfo(
                QDir("/INDIface/INDIin/console"), "*.JPG"));
    TRACE << mpFileInfoQueue->pendingCount();
//    QTimer::singleShot(1000, this, &INDIfaceConsole::nextImage);
//    TRACE << "emit pendingFilesSet()"; // << mPendingFiles;
  //  emit pendingFilesSet();
    EMIT(commandLinePocessed());
    writeLine("Quitting.....");
    writeErr("Quitting.....");
    QTimer::singleShot(1000, core(), &QCoreApplication::quit);
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
