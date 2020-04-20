#include "INDIfaceConsole.h"

#include <QImage>
#include <QTimer>

#include <eirBase/Debug.h>
#include <eirExe/Settings.h>
#include <eirQtCV/eirQtCV.h>
#include <eirQtCV/QtOpenCV.h>


INDIfaceConsole::INDIfaceConsole(Console *parent)
    : Console(parent)
{
    TRACEFN
    setObjectName("INDIfaceConsole");
}

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

QImage INDIfaceConsole::processInputImage(const QImage &inImage,
                                     const int scale) const
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

void INDIfaceConsole::findFaces(const QFileInfo qfi,
                                const QImage &inImage)
{
    TRACEQFI << qfi << inImage;
    BEXPECT(mFrontal);
    BEXPECT(mFrontal->isLoaded());
    mFrontal->setImages(inImage);
}

void INDIfaceConsole::initApplication()
{
    TRACEFN
    writeLine("Welcome to INDIfaceConsole");
    CONNECT(this, &ApplicationHelper::initFinished,
            this, &INDIfaceConsole::initResources);
    CONNECT(this, &INDIfaceConsole::applicationInitd,
            this, &INDIfaceConsole::initResources);
    CONNECT(this, &INDIfaceConsole::resoursesInitd,
            this, &INDIfaceConsole::initTaskLine);
    CONNECT(this, &INDIfaceConsole::taskLineInitd,
            this, &INDIfaceConsole::startTaskLine);
    CONNECT(this, &INDIfaceConsole::processed,
            qApp, &QCoreApplication::quit);
    QTimer::singleShot(100, this, &ApplicationHelper::run);
}

void INDIfaceConsole::initResources()
{
    TRACEFN
/*
    mFrontal = new HaarCascade(ObjectType::FrontalFace,
                               VarPak());
    TSTALLOC(mFrontal)
    TRACE << "Frontal Cascade shell created";
    mFrontal->load(QFileInfo(QDir("../Detectors"),
                             "DefaultFrontalFace.xml"));
    if (mFrontal->isError())
    {
        TRACE << "mFrontal->isError()";
        writeErrs(mFrontal->errorItem().messages());
        errorHandler->submit(mFrontal->errorItem());
    }
    TRACE << "mFrontal no error";
    NEEDDO(mLeftEye)
    NEEDDO(mRightEye)
*/
    emit resoursesInitd();
}

void INDIfaceConsole::initTaskLine()
{
    TRACEFN
    writeLine("INDIfaceConsole loaded");
    NEEDDO(Lots)
    emit taskLineInitd();
}

void INDIfaceConsole::startTaskLine()
{
    TRACEFN
    writeLine("INDIfaceConsole ready");
    NEEDDO(Lots)
    process();
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
        findFaces(qfi, imageIn);
        QTimer::singleShot(100, this, &INDIfaceConsole::nextImage);
    }
}
