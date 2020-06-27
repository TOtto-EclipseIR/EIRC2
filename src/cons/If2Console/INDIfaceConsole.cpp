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
{
    TRACEFN
    setObjectName("INDIfaceConsole");
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
    QString faceHaarFilePath = mpConfig->
        at("Detect/Resources/HaarCascade/Face/XmlFile").value().toString();
    TRACE << "baseHaarDirPath" << baseHaarDirPath;
    TRACE << "faceHaarFilePath" << faceHaarFilePath;
    QFileInfo faceCascadeFileInfo(QDir(baseHaarDirPath),
                                  faceHaarFilePath);
    TRACE << faceCascadeFileInfo.absoluteFilePath()
          << faceCascadeFileInfo.exists()
          << faceCascadeFileInfo.isReadable();
    QFile faceFile(faceCascadeFileInfo.filePath());
    TRACE << faceFile.fileName()
          << faceFile.exists()
          << faceFile.isReadable();
    WEXPECT(faceFile.open(QIODevice::ReadOnly
                          | QIODevice::Text
                          | QIODevice::ExistingOnly));
    WEXPECT(faceFile.isReadable());
    faceFile.close();
//    XmlFile faceXmlElement(faceCascadeFileInfo.filePath());
    NEEDDO(close mpFaceCascade);
    mpFaceCascade = new RectCascade();
    TSTALLOC(mpFaceCascade);
    bool loaded = mpFaceCascade->load(faceCascadeFileInfo.filePath());
    DUMPVAL(loaded);
    WEXPECT(loaded);
    NEEDDO(mFaceFinder.config());

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
    writeLine(QString("===Processing: %1").arg(mCurrentImageFileName));
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

    EXPECT(mFaceFinder.loadImage(mCurrentImageFileName));
    int faceCount = mFaceFinder.find(mFaceParms);
    writeLine("   " + QString::number(faceCount)
              + " Face Rectangles Detected");
    QFileInfo inputFI(mCurrentImageFileName);
    QFileInfo rectFI(mRectDir,
                     inputFI.completeBaseName()+".PNG");
    mFaceFinder.rectImage().save(rectFI.filePath());
    NEEDDO(more);
    TRACERTV()
}
