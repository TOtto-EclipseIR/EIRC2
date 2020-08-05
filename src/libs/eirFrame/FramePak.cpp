#include "FramePak.h"

#include <QDataStream>

#include <eirXfr/Debug.h>

FramePak::FramePak()
{

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

Frame FramePak::toFrame(const QImage &image) const
{
    return *(Frame *)(&image);
}
