#include "FramePak.h"

#include <QDataStream>
#include <QFile>

#include <eirType/Success.h>
#include <eirXfr/Debug.h>

FramePak::FramePak()
{

}

FramePak::FramePak(const QString &inputFileName)
{
    setInputFrame(inputFileName);
}

Frame FramePak::frame() const
{
    return frameAt(0);
}
Frame FramePak::face(const int index) const
{
    return frameAt(index);
}

QString FramePak::toString() const
{
    return frame().fileInfo().filePath();
}

QString FramePak::operator()() const
{
    return toString();
}

bool FramePak::setInputFrame(const QString &inputFileName)
{
    TRACEQFI << inputFileName;
    QFileInfo qfi(inputFileName);
    return setInputFrame(qfi);
}

bool FramePak::setInputFrame(const QFileInfo &inputFileInfo)
{
    TRACEQFI << inputFileInfo;
    Success success(true);
    QFile * file = new QFile();
    TSTALLOC(file);
    QByteArray bytes;
    QImage image;
    Value value;
    if (success) success = inputFileInfo.exists();
    if (success) success = inputFileInfo.isReadable();
//    if (success) success = image.load(inputFileInfo.absoluteFilePath());
    if (success) file->setFileName(inputFileInfo.absoluteFilePath());
    if (success) success = file->open(QIODevice::ReadOnly);
    if (success) bytes = file->readAll();
    if (success) image = QImage::fromData(bytes);
    if (success) success = ! image.isNull();
    if (success) value.set("InputImage", image);
    if (success) ValuePak::set(bytes);
    if (success) ValuePak::set(0, value);
    return success;
}

void FramePak::setFrameRectangles(const QList<QRect> &rects)
{
    QDataStream data;
    data << rects;
    Value value("Frame/PreScan/Rectangles",
                QVariant(data));
    ValuePak::set(1, value);
}

// protected
Frame FramePak::frameAt(const int index) const
{
    TRACEQFI << index;
    QVariant varFrame = ValuePak::value(index);
    QDataStream dsFrame;
    dsFrame << varFrame;
    QImage imgFrame;
    dsFrame >> imgFrame;
    return toFrame(imgFrame);
}

// protected
Frame FramePak::toFrame(const QImage &image) const
{
    return *(Frame *)(&image);
}

void FramePak::setPreScanImage(const QImage &detectImage)
{
    TRACEQFI << detectImage.size() << detectImage.format();
    QDataStream data;
    data << detectImage;
    Value value("Frame/PreScan/DetectImage",
                QVariant(data));
    ValuePak::set(2, value);
}
