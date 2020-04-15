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
    mInputDir.setPath("D:/INDIface/INDIin/Console");
    mOutputDir.setPath("D:/INDIface/INDIout/Console");
    mOutputDir.mkpath(".");
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

QImage INDIfaceConsole::processImage(const QImage &inImage,
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
    writeLine("INDIfaceConsole initialized");
    NEEDDO(Lots)
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
        QImage imageIn = QImage(qfi.filePath());
        int downScale = calculateScale(imageIn.size());
        QImage imageOut = processImage(imageIn, downScale);
        QFileInfo outFI = mOutputDir.filePath(qfi.fileName());
        TRACE << outFI.filePath();
//        WEXPECT(outFI.isWritable());
        WEXPECT(imageOut.save(outFI.filePath()));
        QTimer::singleShot(100, this, &INDIfaceConsole::nextImage);
    }
}
