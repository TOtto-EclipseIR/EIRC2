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
    , mFaceFinder(mpConfig, RectFinderClass::Face)
{
    TRACEFN; TODO(Left/RightEye then Nose & Mouth RectFinders);
    setObjectName("INDIfaceConsole");
    QTimer::singleShot(100, this, &INDIfaceConsole::initializeApplication);
    TRACERTV();
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
    TODO(cvVersion);
//    cvVersion opencvVersion;
  //  writeLine("==="+opencvVersion.toString());
    EMIT(applicationInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::setupCommandLine);
}


void INDIfaceConsole::setupCommandLine()
{
    TRACEFN
    If2CommandLine interface;
    commandLine()->set(&interface);
    commandLine()->process();
    commandLine()->set(nullptr);
    commandLine()->expandDirectories();
    EMIT(commandLineSetup());
    QTimer::singleShot(100, this,
            &INDIfaceConsole::setConfiguration);
}

void INDIfaceConsole::setConfiguration()
{
    TRACEFN
    mpConfig->set(commandLine()->configuration());
    NEEDDO(mFaceFinder.configure());
    QTimer::singleShot(100, this,
            &INDIfaceConsole::initializeResources);
}

void INDIfaceConsole::initializeResources()
{
    TRACEQFI << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INDIfaceConsole::initializeResources()";
#if true
    EXPECT(mFaceFinder.loadResources());
    QSize sz = mFaceFinder.coreSize();
    writeLine(QString("+++Cascade loaded: %1x%2")
              .arg(sz.width()).arg(sz.height())
              .arg(mFaceFinder.cascadeFileInfo().filePath()));
#else
    MUSTDO(Handle Cascade Loading);

    if (mpFaceCascade) mpFaceCascade->close();

    QFileInfo faceCascadeFileInfo(
                QDir(mpConfig->at("Detect/Resources/BaseDir")
                     .value().toString()),
                mpConfig->at("Detect/Resources/HaarCascade/Face/XmlFile")
                    .value().toString());
    TRACE << faceCascadeFileInfo.absoluteFilePath()
          << faceCascadeFileInfo.exists()
          << faceCascadeFileInfo.isReadable();
#ifndef NDEBUG
    XmlFile faceXmlFile(faceCascadeFileInfo.absoluteFilePath());
    EXPECT(faceXmlFile.rootElement().isElement());
    faceXmlFile.close();
#endif
    mpFaceCascade = new RectCascade();
    TSTALLOC(mpFaceCascade);
    EXPECT(mpFaceCascade->load(faceCascadeFileInfo));
    mFaceParms.configure(mpFaceCascade->coreSize(), mpConfig->configuration("Detect/Face"));
    NEEDDO(mFaceFinder.config());
#endif

    QString rectDirString("/INDIface/INDIout/@/Rect");
    rectDirString.replace("@", QDateTime::currentDateTime()
        .toString("DyyyyMMdd-Thhmm"));
    mRectDir = QDir(rectDirString);
    mRectDir.mkpath(".");
    mRectDir.cd(".");

    EMIT(resoursesInitd());
    QTimer::singleShot(100, this, &INDIfaceConsole::startProcessing);
}

void INDIfaceConsole::startProcessing()
{
    TRACEFN
    mImageFileQueue = commandLine()->positionalArgumentList();
    TRACE << mImageFileQueue;
    TODO(?)
    BEXPECT(mFaceFinder.isReadyImage());
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
        mCurrentImageFileName = filePathName;
        QTimer::singleShot(100, this, &INDIfaceConsole::processFile);
        return;                                             /* /=====\ */
    }
    QTimer::singleShot(100, this, &INDIfaceConsole::finishProcessing);
}                                                           /* \=====/ */

void INDIfaceConsole::processFile()
{
    TRACEQFI << "mCurrentImageFile:" << mCurrentImageFileName;
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
    TRACEQFI << mCurrentImageFileName;

    writeLine(QString("===Processing: %1").arg(mCurrentImageFileName));
    EXPECT(mFaceFinder.setInputImage(mCurrentImageFileName));
    int faceCount = mFaceFinder.find();
    writeLine("   " + QString::number(faceCount)
              + " Face Rectangles Detected");
    QFileInfo inputFI(mCurrentImageFileName);
    QFileInfo rectFI(mRectDir,
                     inputFI.completeBaseName()+".PNG");
    bool rectImageSaved = mFaceFinder.rectImage()
            .save(rectFI.filePath(), "PNG");
    EXPECT(rectImageSaved);
    EXPECT(rectFI.exists());
    if (rectImageSaved && rectFI.exists())
        writeLine("    " + rectFI.absoluteFilePath() + "saved");
    NEEDDO(more);
    TRACERTV()
}
