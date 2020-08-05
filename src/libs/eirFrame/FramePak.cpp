#include "FramePak.h"

#include <QDataStream>

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
    Success success(true);
    QFileInfo qfi(inputFileName);
    QImage image;
    if (success) success = qfi.exists();
    if (success) success = qfi.isReadable();
    if (success) success = image.load(inputFileName);
    Value value("InputImage", image);
    if (success) ValuePak::set(0, value);
    return success;
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
