// file: {repo: EIRC2}./src/cons/INDIfaceConsole.cpp
#include "INDIfaceConsole.h"

#include <QDateTime>
#include <QFileInfo>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirType/QQFileInfo.h>
#include <eirExe/CommandLine.h>
#include <eirExe/CommandLineClientInterface.h>
#include <eirExe/ConfigObject.h>
#include <eirExe/FileInfoQueue.h>
#include <eirExe/FileName.h>
#include <eirExe/LegacySettings.h>
#include <eirHaar/cvVersion.h>
#include <eirImage/ImagePakWriterQueue.h>

#include "If2CommandLine.h"

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
//    cvVersion opencvVersion;
  //  writeLine("==="+opencvVersion.toString());
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
/*
    mWriterFlags.bitRef("ImageOutputCapture")
            = mpConfig->contains("/Output/Dirs/Acquire/CaptureDir");
    mWriterFlags.bitRef("ImageOutputInput")
            = mpConfig->contains("/Output/Dirs/Acquire/InputDir");
    mWriterFlags.bitRef("ImageOutputInputGrey")
            = mpConfig->contains("/Output/Dirs/Acquire/InputGreyDir");
    mWriterFlags.bitRef("ImageOutputMarked")
            = mpConfig->contains("/Output/Dirs/Detect/MarkedDir");
*/


    QTimer::singleShot(100, this, &INDIfaceConsole::initializeResources);
}

void INDIfaceConsole::initializeResources()
{
    TRACEQFI << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INDIfaceConsole::initializeResources()";
    QString baseHaarDirPath = mpConfig->
        at("Detect/Resources/BaseDir").value().toString();
    FileName haarCatalogXmlFile = mpConfig->
        at("Detect/Resources/Catalog/XmlFile").value().toString();
    TRACE << "baseHaarDirPath" << baseHaarDirPath;
    TRACE << "haarCatalogXmlFile" << haarCatalogXmlFile;
//    mHaarCatalog.set(baseHaarDirPath);
  //  EXPECT(mHaarCatalog.load(haarCatalogXmlFile));

#if 0
    mpPakWriter = new ImagePakWriterQueue(this);
    TSTALLOC(mpPakWriter);
    mpPakWriter->configureOutput(mpConfig->configuration("Output"));
#endif
    NEEDDO("rectFinder::initialize() x 3~5")
    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::startProcessing);
}

void INDIfaceConsole::startProcessing()
{
    TRACEFN
    mImageFileQueue = commandLine()->positionalArgumentList();
    TRACE << mImageFileQueue;
    TODO(?)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::nextFile()
{
    TRACEQFI << "mImageFileQueue.size()" << mImageFileQueue.size();
    while ( ! mImageFileQueue.isEmpty())                    /* /-----\ */
    {
        QString filePathName = mImageFileQueue.takeFirst();
        TRACEQFI << filePathName << "taken" << mImageFileQueue.size();
        if (filePathName.isEmpty())  continue;              /* \-----/ */
        mCurrentImageFile = filePathName;
        QTimer::singleShot(100, this, &INDIfaceConsole::processFile);
        return;
    }
    QTimer::singleShot(100, this, &INDIfaceConsole::finishProcessing);
}

void INDIfaceConsole::processFile()
{
    TRACEQFI << "mCurrentImageFile:" << mCurrentImageFile;
    writeLine(QString("===Processing: %1").arg(mCurrentImageFile));
#if 1
    mCurrentImage.image().load(mCurrentImageFile);
#else
    QFile file(mCurrentImageFile, this);
    EXPECT(file.open(QIODevice::ReadOnly))
    QByteArray qba = file.readAll();
    QImage tempImage = QImage::fromData(qba);
    mCurrentImage = ColorImage(tempImage);
    QFileInfo qfi(mCurrentImageFile);
    mImagePak.set(qfi, qba);
    mImagePak.set(mCurrentImage.image());
    mImagePak.insert("InputImage/FileName", mCurrentImageFile);
    mImagePak.insert("InputImage/FileInfo", QVariant());
#endif
    EXPECTNOT(mCurrentImage.isNull());
    if ( ! mCurrentImage.isNull())
        processImage();
    TODO(more?)
    QTimer::singleShot(100, this, &INDIfaceConsole::nextFile);
}

void INDIfaceConsole::finishProcessing()
{
    TRACEFN
    NEEDDO(it)
    QTimer::singleShot(100, core(), &QCoreApplication::quit);
}

void INDIfaceConsole::processImage()
{
    TRACEQFI << mCurrentImage.size();
    NEEDDO(it);
    TRACERTV()
}
